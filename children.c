/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:18:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/12 16:29:09 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path(char *arg)
{
	if (*arg == '/' || !ft_strncmp(arg, "./", 2))
	{
		if (!access(arg, F_OK | X_OK))
			return (1);
	}
	return (0);
}

void	only_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	pipex.child_id[0] = fork();
	if (!pipex.child_id[0])
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		get_file_des(&pipex, command->redirect);
		if (is_path(command->args[0]))
			pipex.cmd_path = command->args[0];
		else
			pipex.cmd_path = find_comm_path(command->args[0]);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
		printf("args[0] = %s\n", command->args[0]);
		if (!command->args[0])
			exit(errno);
		if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: %s: command not found\n", command->args[0]);
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
		get_file_des(&pipex, command->redirect);
		if (is_path(command->args[0]))
			pipex.cmd_path = command->args[0];
		else
			pipex.cmd_path = find_comm_path(command->args[0]);
		close(pipex.pipes[0][0]);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
		else
			(dup2(pipex.pipes[0][1], STDOUT), close(pipex.pipes[0][1]));
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: %s: command not found\n", command->args[0]);
		exit(errno);
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
		get_file_des(&pipex, command->redirect);
		if (is_path(command->args[0]))
			pipex.cmd_path = command->args[0];
		else
			pipex.cmd_path = find_comm_path(command->args[0]);
		close(pipex.pipes[i][0]);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		else
			(dup2(pipex.pipes[i - 1][0], STDIN),
			close(pipex.pipes[i - 1][0]));
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
		else
			(dup2(pipex.pipes[i][1], STDOUT), close(pipex.pipes[i][1]));
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: %s: command not found\n", command->args[0]);
		exit(errno);
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
		if (is_path(command->args[0]))
			pipex.cmd_path = command->args[0];
		else
			pipex.cmd_path = find_comm_path(command->args[0]);
		if (mini->curr_heredoc < mini->in_heredocs)
			heredoc_fd = open_heredoc_file(mini);
		if (heredoc_fd != -1)
			(dup2(heredoc_fd, STDIN), close(heredoc_fd));
		else if (pipex.in_fd != -1)
			(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
		else
			(dup2(pipex.pipes[i - 1][0], STDIN), close(pipex.pipes[i - 1][0]));
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
		if (!call_builtins(command, mini)
			&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: %s: command not found\n", command->args[0]);
		exit(errno);
	}
	return (pipex);
}
