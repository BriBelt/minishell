/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 18:44:31 by bbeltran         ###   ########.fr       */
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
