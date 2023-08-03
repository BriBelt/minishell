/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:12:02 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/03 16:22:57 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("new_data: %s\n", new_data);
		ptr->data = new_data;
		printf("new_data assigned: %s\n", ptr->data);
		ptr = ptr->next;
	}
}
