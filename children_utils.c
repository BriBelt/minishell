/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:45:32 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/08 12:00:07 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (ft_strnstr(paths[i], "munki", ft_strlen(paths[i])))
			return (NULL);
		com_path = ft_strjoin(tmp, data);
		free(tmp);
		if (!access(com_path, F_OK | X_OK))
			return (free_2d_array(paths), com_path);
		free(com_path);
		i++;
	}
	return (com_path);
}

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
		if (curr->type == OUTPUT)
			out_count++;
		curr = curr->next;
	}
	if (type == INPUT)
		return (in_count);
	if (type == OUTPUT)
		return (out_count);
	return (0);
}

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
		(*pipex).out_fd = open(out->data, O_WRONLY);
	}
}
