/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:21:09 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/09 13:32:47 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_basic is the structure that will be used for creating a **basic list.
 * This **basic list will contain the quote/space separated readline from
 * the user inside their node->data. This **basic list will later be used
 * to create the t_lexer **lex. */
/* Creates a node for the t_basic structure. */
t_basic	*ft_basic_new(char *content, int join)
{
	t_basic	*node;

	node = malloc(sizeof(t_basic));
	if (!node)
		return (NULL);
	node->data = content;
	if (join > 0)
		node->join = 1;
	else if (join == 0)
		node->join = 0;
	node->next = NULL;
	return (node);
}

/* Inserts a node at the end of our t_basic **basic list. */
void	ft_basic_insert(t_basic	**lst, char *content, size_t join)
{
	t_basic	*node;
	t_basic	*ptr;

	node = ft_basic_new(content, join);
	if (*lst == NULL)
		*lst = node;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}

/* Counts the quotes found inside the user readline, this function will
 * later be used for creating the list. */
int	found_quote(char *rd, size_t *join)
{
	int	i;
	int	count;
	int	first;

	i = -1;
	count = 0;
	first = -1;
	while (rd[++i])
	{
		if (quote_type(rd[i]))
		{
			if (first == -1)
			{
				count++;
				first = i++;
			}
			if (rd[i] == rd[first])
			{
				if (count && rd[i + 1] && rd[i + 1] != ' ')
					(*join)++;
				count++;
			}
		}
		if (count % 2 == 0)
			first = -1;
	}
	return (count);
}

/* Creates a t_basic **basic list from the received readline.
 * First, calls the found_quote(); and checks it result, if 
 * the module of that between 2, is NOT zero, that means the
 * quotes are not closed. Next, with the handle_quotes();*/
t_basic	**create_basic_lst(char *rd)
{
	t_basic	**basic;
	size_t	i;
	size_t	rd_len;
	int		found;
	size_t	join;

	join = 0;
	found = found_quote(rd, &join);
	if (found % 2 != 0)
	{
		perror("create_basic: All quotes must be closed.");
		exit (1);
	}
	basic = malloc(sizeof(t_basic *));
	*basic = NULL;
	i = 0;
	rd_len = ft_strlen(rd);
	if (found && found % 2 == 0)
	{
		while (i < rd_len)
			ft_basic_insert(basic, handle_quotes(rd, &i), join--);
	}
	else if (!found)
	{
		while (i < rd_len)
			ft_basic_insert(basic, split_quote_sens(rd, &i), join--);
	}
	return (basic);
}
