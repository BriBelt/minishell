/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:12:02 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/08 08:56:27 by jaimmart32       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function extracts quoted substrings from data. It iterates through the 
input string and finds the opening and closing quotes (single or double).
If quotes are found, it creates a new array of strings (clean) using ft_split, 
and returns it. If the quotes are not closed properly, the function displays 
an error message and exits the program.*/
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

/* This function cleans the quotes from the data in each node of the linked 
list.For each node, it calls quotes_in_node() to extract the substrings 
without quotes, if there are more than 1 string, uses strjoin(), then updates 
data field with new_data.*/
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

/*This function is used to split the input string data based on spaces but 
considering quoted regions, avoiding spliting those regions.*/
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
