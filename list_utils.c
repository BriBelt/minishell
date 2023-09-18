/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:23:21 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/15 16:08:34 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a new t_lexer *node, with the given *content, which will be
 * the node->data, and the given i, that becomes the node->index. */
t_lexer	*ft_lexernew(char *content, int i, size_t join)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->data = content;
	node->join = join;
	node->next = NULL;
	node->index = i;
	return (node);
}

/* Inserts the t_lexer *node created with ft_lexernew(); at the end of the
 * list. */
void	ft_lexer_insert(t_lexer	**lst, char *content, int i, size_t join)
{
	t_lexer	*node;
	t_lexer	*ptr;

	if (content[0] == '\0')
		return ;
	node = ft_lexernew(content, i, join);
	if (*lst == NULL)
		*lst = node;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}
