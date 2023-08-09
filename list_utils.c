/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:23:21 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/09 16:45:00 by bbeltran         ###   ########.fr       */
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
	if (join > 0)
		node->join = 1;
	else
		node->join = 0;
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

/* Using ft_lexer_insert(); iterates the given array (char **) assigning
 * each array[i] (string) to the node->data. */
t_lexer	**create_lexer(t_basic **basic)
{
	size_t	i;
	int		n;
	t_lexer	**lst;
	t_basic	*curr;
	size_t	join;

	n = 0;
	join = 0;
	lst = malloc(sizeof(t_lexer *));
	if (!lst)
		return (NULL);
	*lst = NULL;
	curr = *basic;
	while (curr)
	{
		i = 0;
		join = curr->join;
		while (i < ft_strlen(curr->data))
			/*Error n still adds to itself if the node content is null*/
			ft_lexer_insert(lst, split_quote_sens(curr->data, &i), n++, join);
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
