/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:45:32 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 16:38:09 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to pass norminette, does the process of changing the fds of output
 * depending if there's an output redirect or not. */
void	child_out_fd(t_pipex pipex, int i, int child_num)
{
	if (child_num == 1)
	{
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
	}
	else
	{
		if (pipex.out_fd != -1)
			(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
		else
			(dup2(pipex.pipes[i][1], STDOUT), close(pipex.pipes[i][1]));
	}
}

/*	Gets the command path that was given to the child process.	*/
char	*get_child_path(t_command *command, t_shell *mini)
{
	char	*cmd_path;

	if (is_path(command->args[0]))
		cmd_path = command->args[0];
	else
		cmd_path = find_comm_path(mini, command->args[0]);
	return (cmd_path);
}

/*	Checks if the given argument is a path instead of a simple command or
 *	something else like an executable or a file.	*/
int	is_path(char *arg)
{
	if (!arg)
		return (0);
	if (*arg == '/' || !ft_strncmp(arg, "./", 2))
	{
		if (!access(arg, F_OK | X_OK))
			return (1);
	}
	return (0);
}

/* This function checks the redirect list, counting the number
 * of redirects of the especified type. Depending on the type returns
 * either OUTPUT, INPUT or APPEND count. */
int	found_redirect_type(t_red **redirect, int type)
{
	t_red	*curr;
	int		in_count;
	int		out_count;

	curr = *redirect;
	in_count = 0;
	out_count = 0;
	while (curr)
	{
		if (curr->type == INPUT)
			in_count++;
		if (curr->type == OUTPUT || curr->type == APPEND)
			out_count++;
		curr = curr->next;
	}
	if (type == INPUT)
		return (in_count);
	if (type == OUTPUT)
		return (out_count);
	return (0);
}

/*	Gets the file descriptors of all the redirects.	*/
void	get_file_des(t_pipex *pipex, t_red **redirect)
{
	t_red	*out;
	t_red	*in;

	out = NULL;
	in = NULL;
	if (found_redirect_type(redirect, INPUT))
	{
		in = last_redirect(redirect, INPUT);
		(*pipex).in_fd = open(in->data, O_RDWR);
	}
	if (found_redirect_type(redirect, OUTPUT))
	{
		out = last_redirect(redirect, OUTPUT);
		if (out->type == APPEND)
			(*pipex).out_fd = open(out->data, O_WRONLY | O_APPEND);
		else
			(*pipex).out_fd = open(out->data, O_WRONLY | O_TRUNC);
	}
}
