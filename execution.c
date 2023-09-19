/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/19 11:22:48 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_builtin(t_shell *mini, t_pipex pipex)
{
	int	here_fd;

	here_fd = -1;
	get_file_des(&pipex, (*mini->cmds)->redirect);
	if (mini->curr_heredoc < mini->in_heredocs)
		here_fd = open_heredoc_file(mini);
	if (here_fd != -1)
		(dup2(here_fd, STDIN), close(here_fd));
	else if (pipex.in_fd != -1)
		(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
	if (pipex.out_fd != -1)
		(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
	call_builtins(*mini->cmds, mini);
}

/* First case for execution(); Checks if the only node from the mini->cmds is
 * a builtin, if not, calls the only_child(); function. */
t_pipex	execute_one(t_shell *mini, t_pipex pipex)
{
	mini->curr_heredoc = 0;
	if (check_redir_access(mini->lex))
	{
		if (builtin_arg(*mini->cmds))
			exec_one_builtin(mini, pipex);
		else
			only_child(pipex, *mini->cmds, mini);
	}
	return (pipex);
}

/* Second case for execution();. Only creates one pipe and calls first_child();
 * and last_child();. */
t_pipex	execute_two(t_shell *mini, t_pipex pipex)
{
	mini->curr_heredoc = 0;
	if (check_redir_access(mini->lex))
	{
		pipe(pipex.pipes[0]);
		pipex = first_child(pipex, *mini->cmds, mini);
		mini->curr_heredoc++;
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

	mini->curr_heredoc = 0;
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
			mini->curr_heredoc++;
		}
	}
	return (pipex);
}

void	delete_all_files(int in_heredocs)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < in_heredocs)
	{
		name = ft_strjoin("/tmp/.heredoc_", ft_itoa(i));
		unlink(name);
		free(name);
	}
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
	int		exited;

	exited = 0;
	mini->in_heredocs = count_input_heredocs(mini->cmds);
	if (here_counter(mini->cmds))
		exited = here_doc_exe(mini->cmds);
	pipex = pipex_init();
	count = command_counter(mini->cmds);
	if (count == 1 && exited != 1)
		pipex = execute_one(mini, pipex);
	else if (count == 2 && !exited)
		pipex = execute_two(mini, pipex);
	else if (count > 2 && !exited)
		pipex = execute_all(mini, pipex, count);
	if (count > 0 && check_for_children(mini->lex))
		wait_for_child(pipex, count, mini);
	delete_all_files(mini->in_heredocs);
}
