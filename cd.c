/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:03:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 16:53:58 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cd builtin function, checks if the node->next of the given node exists if it
 * does exist, calls chdir(); with the node->next->data(desired destination)
 * to move to that directory, if the directory does not exist or doesn't 
 * have the correct permissions, returns an error message. */
void	ft_cd(t_lexer *node, int *times)
{
	t_lexer	*curr;

	if (node->next)
	{
		curr = node->next;
		if (chdir(curr->data) == -1)
			printf("cd: %s: %s\n", node->next->data, strerror(errno));
		while (curr && curr->type != REDIR && curr->type != PIPE)
		{
			curr = curr->next;
			(*times)++;
		}
	}
}
