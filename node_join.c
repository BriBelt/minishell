/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/06 17:11:52 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *				NODE JOIN	
 *  										*/
size_t	join_len(t_basic *node)
{
	t_basic	*curr;
	size_t	len;
	size_t	i;

	curr = node;
	i = 0;
	len = 0;
	while (curr && curr->join == ++i)
	{
		len += ft_strlen(curr->data);
		curr = curr->next;
	}
	return (len);
}

size_t	join_times(t_basic *node)
{
	t_basic	*curr;
	size_t	times;
	size_t	i;

	times = 0;
	i = 0;
	curr = node;
	while (curr && curr->join == ++i)
	{
		times++;
		curr = curr->next;
	}
	return (times);
}

t_lexer	**final_lexer(t_basic **lst)
{
	t_lexer	**lexer;
	t_basic	*curr;
	char	*data;
	t_quote	*h;

	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (NULL);
	*lexer = NULL;
	h = initialize_t_quote();
	curr = *lst;
	while (curr)
	{
		if (curr->join == 1)
		{
			h->end = 0;
			data = ft_calloc(join_len(curr) + 1, sizeof(char));
			h->count = join_times(curr);
			h->first = curr->quote;
			while (++h->end <= h->count)
			{
				data = ft_strjoin(data, curr->data);
				curr = curr->next;
			}
		}
		else
		{
			data = curr->data;
			h->first = curr->quote;
			curr = curr->next;
		}
		ft_lexer_insert(lexer, data, ++h->start, h->first);
	}
	return (lexer);
}
