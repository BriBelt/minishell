/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:21:09 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/14 16:35:14 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_basic is the structure that will be used for creating a **basic list.
 * This **basic list will contain the quote/space separated readline from
 * the user inside their node->data. This **basic list will later be used
 * to create the t_lexer **lex. */
/* Creates a node for the t_basic structure. */
t_basic	*ft_basic_new(char *content, int join)
{
	t_basic	*node;

	node = malloc(sizeof(t_basic));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	node->join = join;
	return (node);
}

/* Inserts a node at the end of our t_basic **basic list. */
void	ft_basic_insert(t_basic	**lst, char *content, size_t join)
{
	t_basic	*node;
	t_basic	*ptr;

	node = ft_basic_new(content, join);
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

/* Counts the quotes found inside the user readline, this function will
 * later be used for creating the list. */
int	found_quote(char *rd, size_t *join)
{
	int	i;
	int	count;
	int	first;

	i = -1;
	count = 0;
	first = -1;
	while (rd[++i])
	{
		if (quote_type(rd[i]))
		{
			if (first == -1)
			{
				count++;
				first = i++;
			}
			if (rd[i] == rd[first])
			{
				if (count && rd[i + 1] && rd[i + 1] != ' ')
					(*join)++;
				count++;
			}
		}
		if (count % 2 == 0)
			first = -1;
	}
	return (count);
}
