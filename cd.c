/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:03:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/05 11:37:19 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cd builtin function, checks if the node->next of the given node exists if it
 * does exist, calls chdir(); with the node->next->data(desired destination)
 * to move to that directory, if the directory does not exist or doesn't 
 * have the correct permissions, returns an error message. */
void	ft_cd(t_lexer *node)
{
	if (node->next)
	{
		if (chdir(node->next->data) == -1)
			printf("Error: %s", strerror(errno));
	}
}
