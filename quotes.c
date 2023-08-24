/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 11:17:50 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	*initialize_t_quote(void)
{
	t_quote	*handle;

	handle = malloc(sizeof(t_quote));
	if (!handle)
		return (NULL);
	handle->normal = 1;
	handle->count = 0;
	handle->start = -1;
	handle->end = 0;
	handle->first = 0;
	return (handle);
}

void	check_closed_quotes(t_basic **pipes)
{
	t_basic	*curr;
	int		closed;
	int		open;
	int		i;

	curr = *pipes;
	closed = -1;
	open = 0;
	while (curr)
	{
		i = -1;
		while (curr->data[++i])
		{
			if (quote_type(curr->data[i]))
			{
				if (!open)
					open = quote_type(curr->data[i++]);
				if (open && quote_type(curr->data[i]) == open && closed == -1)
					closed = i;
			}
		}
		curr = curr->next;
	}
}

char	**quotes_in_node(char *data)
{
	int		i;
	int		open;
	int		closed;
	char	**clean;

	i = -1;
	open = 0;
	closed = -1;
	while (data[++i])
	{
		if (quote_type(data[i]))
		{
			if (!open)
				open = quote_type(data[i++]);
			if (open && quote_type(data[i]) == open && closed == -1)
				closed = i;
		}
	}
	if (open && closed == -1)
		return (printf(QUOTE_ERR), NULL);
	clean = ft_split(data, data[closed]);
	return (clean);
}

void	clean_quotes(t_basic **pipes)
{
	t_basic	*ptr;
	char	**no_quotes;
	char	*new_data;

	ptr = *pipes;
	new_data = NULL;
	while (ptr)
	{
		no_quotes = quotes_in_node(ptr->data);
		if (!no_quotes)
			return ;
		if (no_quotes[0] && no_quotes[1])
			new_data = ft_strjoin(no_quotes[0], no_quotes[1]);
		else if (no_quotes[0] && !no_quotes[1])
			new_data = ft_strdup(no_quotes[0]);
		else if (!no_quotes[0])
			new_data = ft_strdup("");
		free_2D_array(no_quotes);
		ptr->data = new_data;
		ptr = ptr->next;
	}
}

char	*split_quote_sens(char *data, size_t *i)
{
	size_t	start;
	size_t	end;
	size_t	normal;
	char	*new;

	normal = 1;
	end = 0;
	while (data[*i] == ' ')
		(*i)++;
	start = *i;
	while (data[*i])
	{
		if (normal && data[*i] == ' ')
		{
			end = *i;
			break ;
		}
		if (quote_type(data[*i]))
			normal = 0;
		(*i)++;
	}
	if (*i == ft_strlen(data))
		end = ft_strlen(data);
	new = ft_substr(data, start, end - start);
	return (new);
}

char	*handle_quotes(char *rd, size_t	*i)
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
	return (ft_substr(rd, h->start, h->end - h->start));
}
