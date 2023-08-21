/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:29:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 17:30:15 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_redirect(char *data)
{
	int	i;
	int	quote;
	int	redirect;

	i = -1;
	quote = -2;
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
	if (redirect < quote || quote == -2)
		return (quote);
	return (-1);
}

char	*redirect_split(char *data, size_t *i)
{
	size_t	loop;
	size_t	start;
	size_t	end;
	char	*new;

	if (first_redirect(data) == -1)
		return (data);
	start = *i;
	loop = 0;
	end = 0;
	while (data[*i] && data[*i] != '>' && data[*i] != '<')
	{
		loop = 1;
		(*i)++;
	}
	while (data[*i] && (data[*i] == '>' ||data[*i] == '<') && !loop) 
		(*i)++;
	if (*i > (size_t)first_redirect(data))
		*i = ft_strlen(data);
	end = *i;
	new = ft_substr(data, start, end - start);
	return (new);
}

t_basic	**redirect_separate(t_basic **closed_q)
{
	t_basic	**red_basic;
	t_basic	*curr_c;
	size_t	i;
	size_t	join;

	i = 0;
	red_basic = malloc(sizeof(t_basic *));
	if (!red_basic)
		return (NULL);
	*red_basic = NULL;
	curr_c = *closed_q;
	while (curr_c)
	{
		i = 0;
		join = curr_c->join;
		while (i < ft_strlen(curr_c->data))
		{
			if (first_redirect(curr_c->data) != -1)
				ft_basic_insert(red_basic, redirect_split(curr_c->data, &i), join);
			else
				ft_basic_insert(red_basic, split_quote_sens(curr_c->data, &i), join);

		}
		curr_c = curr_c->next;
	}
	return (red_basic);
}

int valid_redirects(char *data)
{
	size_t	len;

	len = ft_strlen(data);
	if (!ft_strcmp("<", data) || !ft_strcmp(">", data))
		return (1);
	if (!ft_strcmp("<<", data) || !ft_strcmp(">>", data))
		return (1);
	return (0);
}

int	check_redirects(t_lexer **lex)
{
	t_lexer	*curr;

	curr = *lex;
	while (curr)
	{
		if ((ft_strchr(curr->data, '>') || ft_strchr(curr->data, '<'))
				&& curr->type == 1 && curr->join == 0)
		{
			if (!valid_redirects(curr->data))
				return (perror("Syntax error"), 0);
		}
		curr = curr->next;
	}
	return (1);
}
