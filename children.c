/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:18:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 16:35:27 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Function to pass norminette, takes care and does the corresponding dup2();
 *	for input fds during the child processes.	*/
void	child_in_fd(t_pipex pipex, int i, int heredoc_fd, int child_num)
{
	if (child_num == 1)
	{
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		else
			(dup2(pipex.pipes[i - 1][0], STDIN), close(pipex.pipes[i - 1][0]));
	}
	else if (child_num == 2)
	{
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		else
			(dup2(pipex.pipes[i - 1][0], STDIN), close(pipex.pipes[i - 1][0]));
	}
}

/*	Child execution and change of fds for running commands. This child does
 *	not execute builtins, the parents does it for them.	*/
void	only_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	pipex.child_id[0] = fork();
	if (!pipex.child_id[0])
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		get_file_des(&pipex, command->redirect);
		pipex.cmd_path = get_child_path(command, mini);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		child_out_fd(pipex, 0, 1);
		if (!command->args[0])
			exit(0);
		if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
			(ft_putstr_fd("Execve: command not found\n", 2), exit(127));
		exit(0);
	}
}

t_pipex	first_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	pipex.child_id[0] = fork();
	if (!pipex.child_id[0])
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		(get_file_des(&pipex, command->redirect), close(pipex.pipes[0][0]));
		pipex.cmd_path = get_child_path(command, mini);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		child_out_fd(pipex, 0, 2);
		if (!command->args[0])
			exit(0);
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			(ft_putstr_fd("Execve: command not found\n", 2), exit(127));
		exit(0);
	}
	return (pipex);
}

t_pipex	middle_child(t_pipex pipex, t_command *command, t_shell *mini, int i)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	pipex.child_id[i] = fork();
	if (!pipex.child_id[i])
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		(get_file_des(&pipex, command->redirect), close(pipex.pipes[i][0]));
		pipex.cmd_path = get_child_path(command, mini);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		child_in_fd(pipex, i, heredoc_fd, 1);
		child_out_fd(pipex, i, 2);
		if (!command->args[0])
			exit(0);
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			(ft_putstr_fd("Execve: command not found\n", 2), exit(127));
		exit(0);
	}
	return (pipex);
}

t_pipex	last_child(t_pipex pipex, t_command *command, t_shell *mini, int i)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	pipex.child_id[i] = fork();
	if (!pipex.child_id[i])
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		get_file_des(&pipex, command->redirect);
		pipex.cmd_path = get_child_path(command, mini);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		child_in_fd(pipex, i, heredoc_fd, 2);
		child_out_fd(pipex, 0, 1);
		if (!command->args[0])
			exit(0);
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			(ft_putstr_fd("Execve: command not found\n", 2), exit(127));
		exit(0);
	}
	return (pipex);
}
