/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:18:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/30 14:45:14 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	get_file_des(pipex, command->redirect);
	pipex.child_id = fork();
	if (!pipex.child_id)
	{
		pipex.cmd_path = find_comm_path(command->args[0]);
		dup2(pipex.out_fd, STDOUT);
//		int i = 0;
//		while (command->args[i])
//		{
//			printf("Arg[%i] = %s\n", i, command->args[i]);
//			i++;
//		}
		if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("Execve: Error\n");
	}
}

t_pipex	first_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	if (*command->redirect)
		get_file_des(pipex, command->redirect);
	pipex.child_id = fork();
	if (!pipex.child_id)
	{
		pipex.cmd_path = find_comm_path(command->args[0]);
		close(pipex.pipes[0]);
		if (pipex.in_fd != -1)
			dup2(pipex.in_fd, STDIN);
		if (pipex.out_fd != -1)
			dup2(pipex.out_fd, STDOUT);
		else
			(dup2(pipex.pipes[1], STDOUT), close(pipex.pipes[1]));
		close(pipex.out_fd);
//		int i = 0;
//		while (command->args[i])
//		{
//			printf("Arg[%i] = %s\n", i, command->args[i]);
//			i++;
//		}
		close(pipex.in_fd);
		close(pipex.out_fd);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("FIRST Execve: Error\n");
		}
	}
	return (pipex);
}

void	last_child(t_pipex pipex, t_command *command, t_shell *mini)
{
	if (*command->redirect)
		get_file_des(pipex, command->redirect);
	pipex.child_id = fork();
	if (!pipex.child_id)
	{
		pipex.cmd_path = find_comm_path(command->args[0]);
		if (pipex.in_fd != -1)
			dup2(pipex.in_fd, STDIN);
		else
			dup2(pipex.pipes[0], STDIN);
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.pipes[0]));
		close(pipex.out_fd);
//		int i = 0;
//		while (command->args[i])
//		{
//			printf("Arg[%i] = %s\n", i, command->args[i]);
//			i++;
//		}
		close(pipex.in_fd);
		close(pipex.out_fd);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("LAST Execve: Error\n");
		}
	}
}
