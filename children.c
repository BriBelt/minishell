/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:18:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/29 18:18:32 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_child(t_pipex *pipex, t_command *command, t_shell *mini)
{
	get_file_des(pipex, command->redirect);
	pipex->child_id = fork();
	if (!pipex->child_id)
	{
		pipex->cmd_path = find_comm_path(command->args[0]);
		dup2(pipex->out_fd, STDOUT);
		if (execve(pipex->cmd_path, command->args, mini->envp) == -1)
			printf("Execve: Error\n");
	}
}

void	first_child(t_pipex *pipex, t_command *command, t_shell *mini)
{
	get_file_des(pipex, command->redirect);
	pipex->child_id = fork();
	if (!pipex->child_id)
	{
		pipex->cmd_path = find_comm_path(command->args[0]);
		close(pipex->pipes[0]);
		if (pipex->in_fd)
			dup2(pipex->in_fd, STDIN);
		if (pipex->out_fd)
			dup2(pipex->out_fd, STDOUT);
		else
			dup2(pipex->pipes[1], STDOUT);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex->cmd_path, command->args, mini->envp) == -1)
				printf("FIRST Execve: Error\n");
		}
	}
}

void	last_child(t_pipex *pipex, t_command *command, t_shell *mini)
{
	get_file_des(pipex, command->redirect);
	pipex->child_id = fork();
	if (!pipex->child_id)
	{
		pipex->cmd_path = find_comm_path(command->args[0]);
		close(pipex->pipes[1]);
		if (pipex->in_fd)
			dup2(pipex->in_fd, STDIN);
		else
			dup2(pipex->pipes[0], STDIN);
		if (pipex->out_fd)
			dup2(pipex->out_fd, STDOUT);
		close(pipex->pipes[0]);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex->cmd_path, command->args, mini->envp) == -1)
				printf("LAST Execve: Error\n");
		}
	}
}
