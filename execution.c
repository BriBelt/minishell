/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 17:52:51 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 1 if a *node->type is a PIPE, else, returns 0. This will be later
 * used to check if we have to create a child process to execute each command
 * or not. */
int	has_pipe(t_lexer **lexer)
{
	t_lexer	*curr;

	curr = *lexer;
	while (curr)
	{
		if (curr->type == PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

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
		com_path = ft_strjoin(tmp, data);
		free(tmp);
		if (!access(com_path, F_OK | X_OK))
			return (free_2D_array(paths), com_path);
		free(com_path);
		i++;
	}
	return (com_path);
}

void	builtin_executor(t_shell *mini)
{
	t_lexer	*curr;
	int		times;

	curr = *mini->lex;
	times = 0;
	while (curr)
	{
		if (curr->type == BUILTIN)
			times = call_builtins(curr, mini);
		if (times > 0)
		{
			while (times--)
				curr = curr->next;
		}
		else
			curr = curr->next;
	}
}

void	get_file_fd(t_pipex pipex, t_red **redirect)
{
	t_red	*in_file;
	t_red	*out_file;

	in_file = last_redirect(redirect, INPUT); 
	out_file = last_redirect(redirect, OUTPUT); 
	if (in_file)
		pipex.in_fd = open(in_file->data, F_OK | O_RDWR);
	if (out_file->type == OUTPUT)
		pipex.out_fd = open(out_file->data, O_CREAT | O_RDWR);
	else if (out_file->type == APPEND)
		pipex.out_fd = open(out_file->data, O_CREAT | O_APPEND | O_RDWR);
}

void	pipex_init(t_pipex pipex, char *cmd, t_red **redirect)
{
	t_pipex	pipex;

	pipex.cmd_path = find_comm_path(cmd);
	pipex.child = 0;
	pipex.pipefd[0] = 0;
	pipex.pipefd[1] = 0;
	get_file_fd(pipex, redirect);
}

void	first_command_child(t_shell *mini, t_command **commands)
{
	t_pipex	pipex;
	
	pipex_init(pipex, commands->args[0], commands->redirect);
	if (pipe(pipex.pipefd) == -1)
	{
//		close pipes
		printf("Error creating the pipe\n");
		exit(errno);
	}
	pipex.child = fork();
	if (pipex.child == 0)
	{
		close(pipex.pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		else
			dup2(pipex.pipefd[1], STDOUT);
		if (execve(pipex.cmd_path, commands->args, mini->envp) == -1)
			printf("%s: command not found\n", command->args[0]);
	}
}

void	middle_command_child(t_shell *mini, t_command **commands)
{
	t_pipex	pipex;
	
	pipex_init(pipex, commands->args[0], commands->redirect);
	if (pipe(pipex.pipefd) == -1)
	{
//		close pipes
		printf("Error creating the pipe\n");
		exit(errno);
	}
	pipex.child = fork();
	if (pipex.child == 0)
	{
		close(pipex.pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		else
			dup2(pipex.pipefd[0], STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		else
			dup2(pipex.pipefd[1], STDOUT);
		if (execve(pipex.cmd_path, commands->args, mini->envp) == -1)
			printf("%s: command not found\n", command->args[0]);
	}
}

void	last_command_child(t_shell *mini, t_command **commands)
{
	t_pipex	pipex;
	
	pipex_init(pipex, commands->args[0], commands->redirect);
	pipex.child = fork();
	if (pipex.child == 0)
	{
		close(pipex.pipefd[0]);
		if (pipex.in_fd)
			dup2(pipex.in_fd, STDIN);
		else
			dup2(pipex.pipefd[0], STDIN);
		if (pipex.out_fd)
			dup2(pipex.out_fd, STDOUT);
		if (execve(pipex.cmd_path, commands->args, mini->envp) == -1)
			printf("%s: command not found\n", command->args[0]);
	}
}

void	command_executor(t_shell *mini, t_command **commands)
{
	t_command	*curr;

	curr = *commands;
	while (curr)
	{

		curr = curr->next;
	}


}
