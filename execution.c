/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 10:00:36 by jaimmart         ###   ########.fr       */
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
