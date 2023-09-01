/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:18:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/01 13:36:56 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	pipex.child_id[0] = fork();
	if (!pipex.child_id[0])
	{
		get_file_des(&pipex, command->redirect);
		pipex.cmd_path = find_comm_path(command->args[0]);
		if (pipex.in_fd != -1)
			dup2(pipex.in_fd, STDIN);
		if (pipex.out_fd != -1)
			dup2(pipex.out_fd, STDOUT);
		if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: %s: command not found\n", command->args[0]);
	}
}

t_pipex	first_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	if (is_command(command->args[0]) == COMMAND
		|| is_builtin(command->args[0]) == BUILTIN)
	{
		pipex.child_id[0] = fork();
		if (!pipex.child_id[0])
		{
			get_file_des(&pipex, command->redirect);
			pipex.cmd_path = find_comm_path(command->args[0]);
			close(pipex.pipes[0][0]);
			if (pipex.in_fd != -1)
				dup2(pipex.in_fd, STDIN);
			if (pipex.out_fd != -1)
				dup2(pipex.out_fd, STDOUT);
			else
				dup2(pipex.pipes[0][1], STDOUT);
			if (!call_builtins(command, mini)
				&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("Execve: %s: command not found\n", command->args[0]);
		}
	}
	else
		printf("%s: command not found\n", command->args[0]);
	return (pipex);
}

t_pipex	middle_child(t_pipex pipex, t_command *command, t_shell *mini, int i)
{
	if (is_command(command->args[0]) == COMMAND
		|| is_builtin(command->args[0]) == BUILTIN)
	{
		pipex.child_id[i] = fork();
		if (!pipex.child_id[i])
		{
			get_file_des(&pipex, command->redirect);
			pipex.cmd_path = find_comm_path(command->args[0]);
			(close(pipex.pipes[i - 1][1]), close(pipex.pipes[i][0]));
			if (pipex.in_fd != -1)
				dup2(pipex.in_fd, STDIN);
			else
				dup2(pipex.pipes[i - 1][0], STDIN);
			if (pipex.out_fd != -1)
				dup2(pipex.out_fd, STDOUT);
			else
				dup2(pipex.pipes[i][1], STDOUT);
			if (!call_builtins(command, mini)
				&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("Execve: %s: command not found\n", command->args[0]);
		}
	}
	else
		printf("%s: command not found\n", command->args[0]);
	return (pipex);
}

t_pipex	last_child(t_pipex pipex, t_command *command, t_shell *mini, int i)
{
	if (is_command(command->args[0]) == COMMAND
		|| is_builtin(command->args[0]) == BUILTIN)
	{
		pipex.child_id[i] = fork();
		if (!pipex.child_id[i])
		{
			get_file_des(&pipex, command->redirect);
			pipex.cmd_path = find_comm_path(command->args[0]);
			close(pipex.pipes[i - 1][1]);
			if (pipex.in_fd != -1)
				dup2(pipex.in_fd, STDIN);
			else
				dup2(pipex.pipes[i - 1][0], STDIN);
			if (pipex.out_fd != -1)
				dup2(pipex.out_fd, STDOUT);
			if (!call_builtins(command, mini)
				&& execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("Execve: %s: command not found\n", command->args[0]);
		}
	}
	else
		printf("%s: command not found\n", command->args[0]);
	return (pipex);
}
