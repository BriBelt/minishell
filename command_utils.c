/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:09:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 19:08:47 by bbeltran         ###   ########.fr       */
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
char	*find_comm_path(t_shell *mini, char *data)
{
	char	*com_path;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (!data)
		return (0);
	paths = get_paths(mini, "PATH");
	com_path = NULL;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (ft_strnstr(paths[i], "munki", ft_strlen(paths[i])))
			return (free(tmp), free_2d_array(paths), NULL);
		com_path = ft_strjoin(tmp, data);
		free(tmp);
		if (!access(com_path, F_OK | X_OK))
			return (free_2d_array(paths), com_path);
		free(com_path);
		i++;
	}
	if (paths)
		free_2d_array(paths);
	return (com_path);
}
