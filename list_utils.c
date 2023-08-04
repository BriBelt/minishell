/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:23:21 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/04 15:53:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a new t_lexer *node, with the given *content, which will be
 * the node->data, and the given i, that becomes the node->index. */
t_lexer	*ft_lexernew(char *content, int i)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	node->index = i;
	return (node);
}

/* Inserts the t_lexer *node created with ft_lexernew(); at the end of the
 * list. */
void	ft_lexer_insert(t_lexer	**lst, char *content, int i)
{
	t_lexer	*node;
	t_lexer	*ptr;

	node = ft_lexernew(content, i);
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

/* Using ft_lexer_insert(); iterates the given array (char **) assigning
 * each array[i] (string) to the node->data. */
t_lexer	**create_lexer(t_basic **basic)
{
	size_t	i;
	int		n;
	t_lexer	**lst;
	t_basic	*curr;

	n = 0;
	lst = malloc(sizeof(t_lexer *));
	if (!lst)
		return (NULL);
	*lst = NULL;
	curr = *basic;
	while (curr)
	{
		i = 0;
		while (i < ft_strlen(curr->data))
			ft_lexer_insert(lst, split_quote_sens(curr->data, &i), n++);
		curr = curr->next;
	}
	return (lst);
}

/*int	count_redirects(t_lexer **lex)
{
	t_lexer	*curr;
	int		count;

	while (curr)
	{
		if (curr->type == 2)
		curr = curr->next;
	}
}*/
