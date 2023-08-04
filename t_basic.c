/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:21:09 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/04 13:10:08 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_basic	*ft_basic_new(char *content)
{
	t_basic	*node;

	node = malloc(sizeof(t_basic));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}

void	ft_basic_insert(t_basic	**lst, char *content)
{
	t_basic	*node;
	t_basic	*ptr;

	node = ft_basic_new(content);
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

int	found_quote(char *rd)
{
	int	i;
	int	count;
	int	first;

	i = -1;
	count = 0;
	first = 0;
	while (rd[++i])
	{
		if (quote_type(rd[i]))
		{
			if (!first)
			{
				count++;
				first = i++;
			}
			if (rd[i] == rd[first])
				count++;
		}
		if (count % 2 == 0)
			first = 0;
	}
	return (count);
}

t_basic	**create_basic_lst(char *rd)
{
	t_basic	**basic;
	size_t	i;
	size_t	rd_len;
	int		found;

	found = found_quote(rd);
	if (found % 2 != 0)
	{
		perror("All quotes must be closed.");
		exit (1);
	}
	basic = malloc(sizeof(t_basic *));
	*basic = NULL;
	i = 0;
	rd_len = ft_strlen(rd);
	if (found && found % 2 == 0)
	{
		while (i < rd_len)
			ft_basic_insert(basic, handle_quotes(rd, &i));
	}
	else if (!found)
	{
		while (i < rd_len)
			ft_basic_insert(basic, split_quote_sens(rd, &i));
	}
	return (basic);
}
