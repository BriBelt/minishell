/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/04 12:03:22 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* First case for execution(); Checks if the only node from the mini->cmds is
 * a builtin, if not, calls the only_child(); function. */
t_pipex pipex_init(void)
{
	t_pipex pipex;

	pipex.in_fd = -1;
	pipex.out_fd = -1;
	return (pipex);
}

/*void	close_pipes(t_pipex pipex, int count)
{
	int i;
	i = 0;
	while (i < count)
	{
		close(pipex.pipes[i][0]);
		close(pipex.pipes[i][1]);
	}

}*/
void wait_for_child(t_pipex pipex, int count)
{
	int i;

	i = 0;
	while (pipex.child_id[i] && i < count)
	{
		waitpid(pipex.child_id[i], NULL, 0);
		i++;
	}
}

t_pipex execute_one(t_shell *mini, t_pipex pipex)
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
		pipex = last_child(pipex, (*mini->cmds)->next, mini, 1);
		(close(pipex.pipes[0][0]), close(pipex.pipes[0][1]));
	}
	return (pipex);
}

/* Function for the final case (count > 2) of execution();.
 * Iterates through the mini->cmds list, creates pipes and executes a
 * different function depending if the node that is about to be executed
 * is the either the first or last, or not. If it's the first node (0),
 * it will call first_child();, if it's the last, it will call last_child();
 * else, it will call middle_child();. */
void	execute_three(t_shell *mini, t_pipex pipex)
{
	pipe(pipex.pipes[0]);
	pipex.child_id[0] = fork();
	if (pipex.child_id[0] == 0)
	{
		close(pipex.pipes[0][0]);
		pipex.cmd_path = find_comm_path((*mini->cmds)->args[0]);
		dup2(pipex.pipes[0][1], STDOUT);
		close(pipex.pipes[0][1]);
		execve(pipex.cmd_path, (*mini->cmds)->args, mini->envp);
	}
	else
	{
		close(pipex.pipes[0][1]);
		pipe(pipex.pipes[1]);
		pipex.child_id[1] = fork();
		if (pipex.child_id[1] == 0)
		{
			close(pipex.pipes[1][0]);
			pipex.cmd_path = find_comm_path((*mini->cmds)->next->args[0]);
			dup2(pipex.pipes[0][0], STDIN);
			close(pipex.pipes[0][0]);
			dup2(pipex.pipes[1][1], STDOUT);
			close(pipex.pipes[1][1]);
			execve(pipex.cmd_path, (*mini->cmds)->next->args, mini->envp);
		}
		else
		{
			close(pipex.pipes[0][0]);
			close(pipex.pipes[1][1]);
			pipex.child_id[2] = fork();
			if (pipex.child_id[2] == 0)
			{
				pipex.cmd_path = find_comm_path((*mini->cmds)->next->next->args[0]);
				dup2(pipex.pipes[1][0], STDIN);
				close(pipex.pipes[1][0]);
				execve(pipex.cmd_path, (*mini->cmds)->next->next->args, mini->envp);
			}
		}
	}
	close(pipex.pipes[1][0]);
}

t_pipex execute_all(t_shell *mini, t_pipex pipex, int count)
{
	t_command *cmd;
	int i;

	if (check_redir_access(mini->lex))
	{
		cmd = *mini->cmds;
		i = 0;
		while (i < count && cmd)
		{
			if (i != count - 1)
				pipe(pipex.pipes[i]);
			if (i == 0)
			{
				pipex = first_child(pipex, cmd, mini);
				close(pipex.pipes[i][1]);
			}
			else if (i == count - 1)
			{
				pipex = last_child(pipex, cmd, mini, i);
				close(pipex.pipes[i - 1][0]);
			}
			else if (i > 0 && i < count - 1)
			{
				pipex = middle_child(pipex, cmd, mini, i);
				close(pipex.pipes[i - 1][0]);
				close(pipex.pipes[i][1]);
			}
			i++;
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
void executor(t_shell *mini)
{
	t_pipex	pipex;
	int		count;

	pipex = pipex_init();
	count = command_counter(mini->cmds);
	if (count == 1)
		pipex = execute_one(mini, pipex);
	else if (count == 2)
		pipex = execute_two(mini, pipex);
//	else if (count == 3)
//		execute_three(mini, pipex);
	else
		pipex = execute_all(mini, pipex, count);
	//	wait_for_child(pipex, count);
	waitpid(pipex.child_id[0], NULL, 0);
	waitpid(pipex.child_id[1], NULL, 0);
	waitpid(pipex.child_id[2], NULL, 0);
	waitpid(pipex.child_id[3], NULL, 0);
	//	waitpid(-1, NULL, 0);
}
