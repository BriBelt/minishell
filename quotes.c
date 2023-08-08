/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/05 15:37:35 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	*initialize_t_quote(void)
{
	t_quote	*handle;

	handle = malloc(sizeof(t_quote));
	handle->normal = 1;
	handle->count = 0;
	handle->start = -1;
	handle->end = 0;
	handle->first = 0;
	return (handle);
}

/*char	*handle_quotes(char	*rd)
{
	int		i;
	int		j;
	int		open;
	int		normal;
	int		closed;
	char	*data;

	i = -1;
	j = 0;
	normal = 1;
	open = 0;
	closed = -1;
	data = ft_calloc(space_needed(rd), sizeof(char));
	while (rd[++i] && j < (int)space_needed(rd))
	{
		if (quote_type(rd[i]))
		{
			normal = 0;
			if (!open)
			{
				open = quote_type(rd[i]);
				data[j++] = rd[i++];
			}
			if (open && quote_type(rd[i]) == open && closed == -1)
				closed = i;
		}
		if (i != closed)
			data[j] = rd[i];
		else if (i == closed || (normal && open && closed == -1))
		{
			data[j] = rd[i];
			data[j + 1] = '!';
			j++;
			open = 0;
			closed = -1;
		}
		j++;
	}
	return (data);
}*/
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
	{
		perror("Quotes must be closed.\n");
		exit(1);
	}
	clean = ft_split(data, data[closed]);
	return (clean);
}

void	clean_quotes(t_lexer **lex)
{
	t_lexer	*ptr;
	char	**no_quotes;
	char	*new_data;
	int		i;

	ptr = *lex;
	while (ptr)
	{
		i = 0;
		no_quotes = quotes_in_node(ptr->data);
		if (no_quotes[1])
			new_data = ft_strjoin(no_quotes[0], no_quotes[1]);
		else if (no_quotes[0] && !no_quotes[1])
			new_data = ft_strdup(no_quotes[0]);
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
/*
char	*handle_quotes(char *rd, size_t	*i)
{
	int		single;
	int		q_double;
	int		normal;
	int		start;
	int		first;
	int		x;
	int		end;
	char	*data;

	normal = 1;
	single = 0;
	q_double = 0;
	start = 0;
	end = 0;
	first = 0;
	x = 0;
	while (rd[*i])
	{
		if (quote_type(rd[*i]))
		{
			normal = 0;
			if (quote_type(rd[*i]) == 1)
				single++;
			else if (quote_type(rd[*i]) == 2)
				q_double++;
			if (!first)
				first = quote_type(rd[*i]);
		}
		if ((single == 2 && first == 1) || (q_double == 2 && first == 2))
		{
			end = (*i) + 1;
			(*i)++;
			break ;
		}
		if (normal && !x)
		{
			x = 1;
			start = *i;
		}
		else if (((single == 1 && first == 1) || (q_double == 1 && first == 2)) && !x)
		{
			x = 1;
			start = *i;
		}
		(*i)++;
	}
	data = ft_substr(rd, start, end - start);
	return (data);
}
*/
