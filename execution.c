/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/08 12:53:45 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* First case for execution(); Checks if the only node from the mini->cmds is
 * a builtin, if not, calls the only_child(); function. */
t_pipex	execute_one(t_shell *mini, t_pipex pipex)
{
	if (!call_builtins(*mini->cmds, mini) && check_redir_access(mini->lex))
		only_child(pipex, *mini->cmds, mini);
	return (pipex);
}

/* Second case for execution();. Only creates one pipe and calls first_child();
 * and last_child();. */
t_pipex	execute_two(t_shell *mini, t_pipex pipex)
{
	if (check_redir_access(mini->lex))
	{
		pipe(pipex.pipes[0]);
		pipex = first_child(pipex, *mini->cmds, mini);
		close(pipex.pipes[0][1]);
		pipex = last_child(pipex, (*mini->cmds)->next, mini, 1);
		close(pipex.pipes[0][0]);
	}
	return (pipex);
}

t_pipex	last_and_middle(t_shell *mini, t_pipex pipex, t_command *cmd, int i)
{
	int	count;

	count = command_counter(mini->cmds);
	if (i == count - 1)
	{
		pipex = last_child(pipex, cmd, mini, i);
		close(pipex.pipes[i - 1][0]);
	}
	else if (i > 0 && i < count - 1)
	{
		pipex = middle_child(pipex, cmd, mini, i);
		(close(pipex.pipes[i - 1][0]), close(pipex.pipes[i][1]));
	}
	return (pipex);
}

/* Function for the final case (count > 2) of execution();.
 * Iterates through the mini->cmds list, creates pipes and executes a
 * different function depending if the node that is about to be executed
 * is the either the first or last, or not. If it's the first node (0),
 * it will call first_child();, if it's the last, it will call last_child();
 * else, it will call middle_child();. */
t_pipex	execute_all(t_shell *mini, t_pipex pipex, int count)
{
	t_command	*cmd;
	int			i;

	if (check_redir_access(mini->lex))
	{
		cmd = *mini->cmds;
		i = -1;
		while (++i < count && cmd)
		{
			if (i != count - 1)
				pipe(pipex.pipes[i]);
			if (i == 0)
			{
				pipex = first_child(pipex, cmd, mini);
				close(pipex.pipes[i][1]);
			}
			else
				pipex = last_and_middle(mini, pipex, cmd, i);
			cmd = cmd->next;
		}
	}
	return (pipex);
}

/* Command and builtin executor, in charge of creating the pipes
 * and child processes that are needed for each command received
 * from the mini->cmds. Counts the amount of commands that the
 * list has, and depending on the result calls one of the three
 * different cases. For one command = execute_one();, for two
 * execute_two();, and for command lists greater than two, calls
 * execute_all(); */
void	executor(t_shell *mini)
{
	t_pipex	pipex;
	int		count;

	if (here_counter(mini->cmds))
		here_doc_exe(mini->cmds);
	pipex = pipex_init();
	count = command_counter(mini->cmds);
	if (count == 1)
		pipex = execute_one(mini, pipex);
	else if (count == 2)
		pipex = execute_two(mini, pipex);
	else
		pipex = execute_all(mini, pipex, count);
	wait_for_child(pipex, count);
}
