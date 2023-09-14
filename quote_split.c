/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:12:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/14 16:35:03 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *				 QUOTE SEPARATION					
 *  											*/
/* This function splits the given *data by the first type of
 * quotes found inside the *data, returns a new string that
 * will later be used by our ft_basic_insert();. */
int	check_for_closed_quotes(char *data)
{
	int	i;
	int	first;
	int	count;

	i = -1;
	count = 0;
	first = 0;
	while (data[++i])
	{
		if (quote_type(data[i]))
		{
			if (!first)
				first = quote_type(data[i]);
			if (quote_type(data[i]) == first)
				count++;
		}
		if (count == 2)
			return (1);
	}
	if (first && count != 2)
		return (printf(QUOTE_ERR), 0);
	return (1);
}

int	quote_list_checker(t_basic **list)
{
	t_basic	*curr;

	curr = *list;
	while (curr)
	{
		if (!check_for_closed_quotes(curr->data))
			return (0);
		curr = curr->next;
	}
	return (1);
}

char	*quote_split(char *rd, int *i)
{
	t_quote	*h;

	h = initialize_t_quote();
	while (rd[*i])
	{
		if (quote_type(rd[*i]))
		{
			h->normal = 0;
			if (!h->first)
				h->first = quote_type(rd[*i]);
			if (quote_type(rd[*i]) == h->first)
				h->count++;
		}
		if (h->count == 2)
		{
			h->end = (*i) + 1;
			(*i)++;
			break ;
		}
		if (h->normal && h->start == -1)
			h->start = *i;
		else if (h->count == 1 && h->first && h->start == -1)
			h->start = *i;
		(*i)++;
	}
	if (h->count == 1 && h->start && !h->end)
		h->end = ft_strlen(rd);
	return (ft_substr(rd, h->start, h->end - h->start));
}

/* Just checks if there's a quote inside the *data. */
int	quote_inside_node(char *data)
{
	if (ft_strchr(data, '\'') || ft_strchr(data, '\"'))
		return (1);
	return (0);
}

/* Creates a new **t_basic going through each node of the
 * given **space_sep list, if the node->data has quotes
 * it calls quote_split();, assigning the join value, by default
 * is 1, but as the function ft_basic_insert(); keeps being called
 * the value of join increments. If there's no quotes in 
 * the node->data, it does a simple ft_basic_insert(); of the node.*/
t_basic	**create_quote_sep(t_basic **space_sep)
{
	t_basic	**quote_sep;
	t_basic	*curr_space;
	size_t	join;
	int		i;

	quote_sep = malloc(sizeof(t_basic *));
	if (!quote_sep)
		return (NULL);
	*quote_sep = NULL;
	curr_space = *space_sep;
	while (curr_space)
	{
		i = 0;
		join = 0;
		if (quote_inside_node(curr_space->data))
		{
			while (i < (int)ft_strlen(curr_space->data))
				ft_basic_insert(quote_sep, quote_split(curr_space->data, &i),
					++join);
		}
		else if (!quote_inside_node(curr_space->data))
			ft_basic_insert(quote_sep, curr_space->data, 0);
		curr_space = curr_space->next;
	}
	return (quote_sep);
}
