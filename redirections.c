/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:29:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/07 15:41:26 by jaimmart32       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*If the first redirection symbol appears before the first quote character, 
it returns 1; otherwise, it returns 0. This is done to avoid handling false
redirections between quotes.*/
int	first_redirect(char *data)
{
	int	i;
	int	quote;
	int	redirect;

	i = -1;
	quote = 0;
	redirect = 0;
	while (data[++i])
	{
		if (data[i] == '<' ||data[i] == '>')
		{
			redirect = i;
			break ;
		}
	}
	i = -1;
	while (data[++i])
	{
		if (quote_type(data[i]))
		{
			quote = i;
			break ;
		}
	}
	if (redirect < quote)
		return (1);
	return (0);
}

/*This function is used to extract substrings from the input data based on 
redirection symbols.*/
char	*redirect_split(char *data, size_t *i)
{
	size_t	loop;
	size_t	start;
	size_t	end;
	char	*new;

	if (!first_redirect(data))
		return (data);
	start = *i;
	loop = 0;
	end = 0;
	while (data[*i]!= '\0' && data[*i] != '>' && data[*i] != '<')
	{
		loop = 1;
		(*i)++;
	}
	while (data[*i] && (data[*i] == '>' ||data[*i] == '<') && !loop) 
		(*i)++;
	end = *i;
	new = ft_substr(data, start, end - start);
	return (new);
}

/*This function takes a linked list of type t_basic(closed_q) and 
processes each element to handle redirections.Then creates a new linked 
list(red_basic) to store the substrings extracted from the data field of 
each t_basic element with redirect_split().*/
t_basic	**redirec_separate(t_basic **closed_q)
{
	t_basic	**red_basic;
	t_basic	*curr_c;
	size_t	i;

	i = 0;
	red_basic = malloc(sizeof(t_basic *));
	*red_basic = NULL;
	curr_c = *closed_q;
	while (curr_c)
	{
		i = 0;
		while (i < ft_strlen(curr_c->data))
			ft_basic_insert(red_basic, redirect_split(curr_c->data, &i));
		curr_c = curr_c->next;
	}
	return (red_basic);
}
