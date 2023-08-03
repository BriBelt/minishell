/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/03 17:46:23 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	*initialize_t_quote(size_t malloc_size)
{
	t_quote	*handle;

	handle = malloc(sizeof(t_quote));
	handle->i = -1;
	handle->j = 0;
	handle->normal = 0;
	handle->open = 0;
	handle->closed = -1;
	handle->data = ft_calloc(malloc_size, sizeof(char));
	return (handle);
}

size_t	space_needed(char *rd)
{
	size_t	i;
	int		open;
	int		closed;
	size_t	spaces;

	i = -1;
	open = 0;
	closed = 0;
	spaces = 0;
	while (rd[++i])
	{
		if (quote_type(rd[i]))
		{
			if (!open)
				open = quote_type(rd[i++]);
			if (open && quote_type(rd[i]) == open)
			{
				spaces++;
				open = 0;
			}
		}
	}
	return (i + spaces);
}

void	found_quote(t_quote *h, char *rd)
{
	if (!h->open)
	{
		h->open = quote_type(rd[h->i]);
		h->data[h->j++] = rd[h->i++];
	}
	if (h->open && quote_type(rd[h->i]) == h->open && h->closed == -1)
		h->closed = h->i;
}

/*char	*separate_quotes(char *rd)
{
	t_quote	*h;

	h = initialize_t_quote(space_needed(rd));
	while (rd[++h->i] && h->j < (int)space_needed(rd))
	{
		if (quote_type(rd[h->i]))
		{
			h->normal = 0;
			found_quote(h, rd);
		}
		if (h->i != h->closed)
			h->data[h->j] = rd[h->i];
		else if (h->i == h->closed
			|| (h->normal && h->open && h->closed == -1))
		{
			h->data[h->j] = rd[h->i];
			h->data[h->j + 1] = '!';
			h->j++;
			h->open = 0;
			h->closed = -1;
		}
		h->j++;
	}
	free(rd);
	return (h->data);
}*/

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
			if (single && !first)
				first = 1;
			else if (q_double && !first)
				first = 2;
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
//		if (normal && quote_type(rd[*i + 1]))
//		{
//			(*i)++;
//			end = *i;
//			break ;
//		}
		(*i)++;
	}
	data = ft_substr(rd, start, end - start);
	return (data);
}

int	main(void)
{
	char	*str = "\"\'first\'\"\"second\"third\'four\'";
	size_t	i = 0;
	
	while (i < ft_strlen(str))
//		handle_quotes(str, &i);
		printf("new= %s\n", handle_quotes(str, &i)); 
}
