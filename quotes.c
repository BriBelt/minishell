/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 16:38:18 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_open_closed(char *data, int *i, int *open, int *closed)
{
	while (data[++(*i)])
	{
		if (quote_type(data[*i]))
		{
			if (!*open)
				*open = quote_type(data[(*i)++]);
			if (*open && quote_type(data[*i]) == *open && *closed == -1)
				*closed = *i;
		}
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
	set_open_closed(data, &i, &open, &closed);
	if (open && closed == -1)
		return (printf(QUOTE_ERR), NULL);
	if (open && closed > -1 && data[closed])
		clean = ft_split(data, data[closed]);
	else
	{
		clean = ft_calloc(2, sizeof(char *));
		if (!clean)
			return (NULL);
		clean[0] = ft_strdup(data);
	}
	free(data);
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
		free_2d_array(no_quotes);
		ptr->data = new_data;
		ptr = ptr->next;
	}
}

/* Splits the data given by spaces, ignoring the spaces
 * inside quotes. Creates and returns a new space-separated
 * string. */
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
