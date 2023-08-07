/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_basic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:21:09 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/07 16:23:51 by jaimmart32       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is used to create a new node of type t_basic.*/
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

/*This function is used to insert a new node into a linked list of type 
t_basic.*/
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

/*This function is used to check if quotes in rd are closed. It only counts 
the first occurrence of quote and the matching quote that closes it if it 
appears. Then it returns the count.*/
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

/*This function is used to create a linked list of t_basic nodes from rd.
It checks if quotes in the string are balanced using the found_quote function.
If not, it displays an error message and exits the program. Then if there are 
quotes it splits rd with handle_quotes(), otherwise it splits it by spaces.*/
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
