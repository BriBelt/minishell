/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 17:08:40 by bbeltran         ###   ########.fr       */
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
	char	*aux;
	t_quote	*h;

	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (NULL);
	*lexer = NULL;
	aux = NULL;
	h = initialize_t_quote();
	curr = *lst;
	while (curr)
	{
		if (curr->join == 1)
		{
			h->end = 0;
			data = ft_calloc(join_len(curr) + 1, sizeof(char));
			if (!data)
				return (NULL);
			h->count = join_times(curr);
			h->first = curr->quote;
			while (++h->end <= h->count)
			{
				aux = data;
				data = ft_strjoin(aux, curr->data);
				curr = curr->next;
				free(aux);
			}
		}
		else
		{
			data = ft_strdup(curr->data);
			h->first = curr->quote;
			curr = curr->next;
		}
		if (data && data[0])
			ft_lexer_insert(lexer, data, ++h->start, h->first);
		else
			free(data);
	}
	return (free(h), lexer);
}
