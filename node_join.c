/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 17:33:17 by bbeltran         ###   ########.fr       */
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

char	*join_data(t_basic *curr, char *data, char *aux, t_quote *h)
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
			(h->i)++;
			curr = curr->next;
			free(aux);
		}
	}
	else
	{
		data = ft_strdup(curr->data);
		h->first = curr->quote;
		(h->i)++;
	}
	return (data);
}

void	insert_or_not(char *data, t_lexer **lexer, t_quote *h)
{
	if (data && data[0])
		ft_lexer_insert(lexer, data, ++h->start, h->first);
	else
		free(data);
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
	data = NULL;
	h = initialize_t_quote();
	curr = *lst;
	while (curr)
	{
		h->i = 0;
		data = join_data(curr, data, aux, h);
		insert_or_not(data, lexer, h);
		while (--(h->i) >= 0)
			curr = curr->next;
	}
	return (free(h), lexer);
}
