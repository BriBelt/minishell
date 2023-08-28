/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/28 16:55:24 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gets posible paths for executables with get_paths() and tries to access 
every path with the node's data append to it. If it access the file 
successfully, returns the correct path so that it can be use in a execve().*/
char	*find_comm_path(char *data)
{
	char	*com_path;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths("PATH");
	com_path = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (ft_strnstr(paths[i], "munki", ft_strlen(paths[i])))
			return (NULL);
		com_path = ft_strjoin(tmp, data);
		free(tmp);
		if (!access(com_path, F_OK | X_OK))
			return (free_2D_array(paths), com_path);
		free(com_path);
		i++;
	}
	return (com_path);
}

void	get_file_fd(t_pipex pipex, t_red **redirect)
{
	t_red	*in_file;
	t_red	*out_file;

	in_file = last_redirect(redirect, INPUT);
	out_file = last_redirect(redirect, OUTPUT);
	if (in_file)
	{
		printf("in fd = %s\n", in_file->data);
		pipex.in_fd = open(in_file->data, F_OK | O_RDWR);
	}
	if (out_file->type == OUTPUT)
	{
		printf("out fd = %s\n", out_file->data);
		pipex.out_fd = open(out_file->data, O_CREAT | O_RDWR);
	}
	else if (out_file->type == APPEND)
	{
		printf("out append fd = %s\n", out_file->data);
		pipex.out_fd = open(out_file->data, O_CREAT | O_APPEND | O_RDWR);
	}
}

void	pipex_init(t_pipex pipex, char *cmd, t_red **redirect)
{
	pipex.cmd_path = find_comm_path(cmd);
	get_file_fd(pipex, redirect);
}

t_pipex	first_command_child(t_shell *mini, t_command *command)
{
	t_pipex	pipex;

	pipex.ids[0] = 0;
	pipex_init(pipex, command->args[0], command->redirect);
	if (pipe(pipex.out_pipefd) == -1)
	{
//		close pipes
		printf("Error creating the pipe\n");
		exit(errno);
	}
	pipex.i = 0;
	pipex.ids[pipex.i] = fork();
	if (pipex.ids[pipex.i] == 0)
	{
		close(pipex.out_pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		else
			dup2(pipex.out_pipefd[1], STDOUT);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("%s: command not found\n", command->args[0]);
		}
	}
	return (pipex);
}

t_pipex	middle_command_child(t_pipex pipex, t_shell *mini, t_command *command)
{
	pipex.in_pipefd[0] = pipex.out_pipefd[0];
	pipex.in_pipefd[1] = pipex.out_pipefd[1];
	pipex.cmd_path = find_comm_path(command->args[0]);
	if (pipe(&pipex.out_fd) == -1)
	{
//		close pipes
		printf("Error creating the pipe\n");
		exit(errno);
	}
	pipex_init(pipex, command->args[0], command->redirect);
	pipex.i++;
	pipex.ids[pipex.i] = fork(); 
	if (pipex.ids[pipex.i] == 0)
	{
		close(pipex.in_pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		else
			dup2(pipex.in_pipefd[0], STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		else
			dup2(pipex.out_pipefd[1], STDOUT);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("%s: command not found\n", command->args[0]);
		}
	}

	return (pipex);
}

void	last_command_child(t_pipex pipex, t_shell *mini, t_command *command)
{
	pipex_init(pipex, command->args[0], command->redirect);
	pipex.in_pipefd[0] = pipex.out_pipefd[0];
	pipex.in_pipefd[1] = pipex.out_pipefd[1];
	pipex.i++;
//	pipex.cmd_path = find_comm_path(command->args[0]);
	pipex.ids[pipex.i] = fork();
	if (pipex.ids[pipex.i] == 0)
	{
		close(pipex.in_pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		else
			dup2(pipex.in_pipefd[0], STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		if (!call_builtins(command, mini))
		{
			if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
				printf("%s: command not found\n", command->args[0]);
		}
	}
}

void	only_child(t_pipex pipex, t_shell *mini, t_command *command)
{
//	t_pipex	pipex;

	printf("before child\n");
//	pipex.ids[0] = fork();
//	printf("created child id = %i\n", pipex.ids[0]);
//	if (pipex.ids[0] == 0)
//	{
//		pipex_init(pipex, command->args[0], command->redirect);
		pipex.cmd_path = find_comm_path(command->args[0]);
		get_file_fd(pipex, command->redirect);
		printf("pipex.in_fd %i\n", pipex.in_fd);
		if (pipex.in_fd)
		{
			printf("in fd\n");
			dup2(pipex.in_fd, STDIN);
		}
		printf("pipex.out_fd %i\n", pipex.out_fd);
		if (pipex.out_fd)
		{
			printf("out fd\n");
			dup2(pipex.out_fd, STDOUT);
		}
		if (execve(pipex.cmd_path, command->args, mini->envp) == -1)
			printf("%s: command not found\n", command->args[0]);
//	}
//	return (pipex);
}

void	wait_for_child(t_pipex pipex)
{
	int	j;

	j = 0;
	while (pipex.ids[j])
	{
		waitpid(pipex.ids[j], NULL, 0);
		j++;
	}
}

int	command_counter(t_command **commands)
{
	t_command	*curr;
	int			count;

	count = 0;
	curr = *commands;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

void	command_executor(t_shell *mini, t_command **commands)
{
	t_command	*curr;
	int			count;
	t_pipex		pipex;

	curr = *commands;
	count = -1;
	while (curr && ++count <= command_counter(commands))
	{
		if (count == 0)
			pipex = first_command_child(mini, curr);
		else if (count < command_counter(commands))
			pipex = middle_command_child(pipex, mini, curr);
		else if (count == command_counter(commands))
			last_command_child(pipex, mini, curr);
		curr = curr->next;
	}
	wait_for_child(pipex);
}

void	executor(t_shell *mini)
{
	t_command	*curr;
	t_pipex		pipex;

	curr = *mini->cmds;
	if (command_counter(mini->cmds) == 1)
	{
		if (!call_builtins(curr, mini))
		{
			pipex.ids[0] = fork();
			if (pipex.ids[0] == 0)
				only_child(pipex, mini, curr);
			wait_for_child(pipex);
		}
	}
	else if (command_counter(mini->cmds) == 2)
	{
		pipex = first_command_child(mini, curr);
		last_command_child(pipex, mini, curr);
		wait_for_child(pipex);
	}
	else
		command_executor(mini, mini->cmds);
}
