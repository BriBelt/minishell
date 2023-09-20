/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:05:34 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 16:17:38 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_pipe(char *data)
{
	int	i;
	int	quote;
	int	pipe;

	i = -1;
	quote = -2;
	pipe = 0;
	while (data[++i])
	{
		if (data[i] == '|')
		{
			pipe = i;
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
	if (pipe < quote || quote == -2)
		return (quote);
	return (-1);
}

char	*pipe_split(char *data, size_t *i)
{
	size_t	loop;
	size_t	start;
	size_t	end;
	char	*new;

	if (first_pipe(data) == -1)
		return (data);
	start = *i;
	loop = 0;
	end = 0;
	while (data[*i] && data[*i] != '|')
	{
		loop = 1;
		(*i)++;
	}
	if (data[*i] && data[*i] == '|' && !loop)
		(*i)++;
	if (*i > (size_t)first_pipe(data))
		*i = ft_strlen(data);
	end = *i;
	new = ft_substr(data, start, end - start);
	return (new);
}

t_basic	**pipe_separate(t_basic **r_basic)
{
	t_basic	**p_basic;
	t_basic	*r_curr;
	size_t	i;
	size_t	join;

	p_basic = malloc(sizeof(t_basic *));
	if (!p_basic)
		return (NULL);
	*p_basic = NULL;
	r_curr = *r_basic;
	while (r_curr)
	{
		i = 0;
		join = r_curr->join;
		while (i < ft_strlen(r_curr->data))
		{
			if (first_pipe(r_curr->data) != -1)
				ft_basic_insert(p_basic, pipe_split(r_curr->data, &i), join);
			else
				ft_basic_insert(p_basic,
					split_quote_sens(r_curr->data, &i), join);
		}
		r_curr = r_curr->next;
	}
	return (p_basic);
}

int	check_pipes(t_lexer **lex)
{
	t_lexer	*curr;

	curr = *lex;
	if (!curr)
		return (0);
	if (curr->type == PIPE && !curr->index)
		return (printf(PIPE_ERR), 0);
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (curr->next == NULL)
				return (printf(PIPE_ERR), 0);
			else
			{
				if (curr->next->type == PIPE)
					return (printf(PIPE_ERR), 0);
			}
		}
		curr = curr->next;
	}
	return (1);
}
