/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:29:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 18:55:31 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (data[*i] && (data[*i] == '>' || data[*i] == '<') && !loop)
		(*i)++;
	if (*i > (size_t)first_redirect(data))
		*i = ft_strlen(data);
	end = *i;
	new = ft_substr(data, start, end - start);
	return (new);
}

void	red_new(t_basic *curr_c, size_t *i, t_basic **red_basic, size_t *join)
{
	while (*i < ft_strlen(curr_c->data))
	{
		if (first_redirect(curr_c->data) != -1)
			ft_basic_insert(red_basic,
				redirect_split(curr_c->data, i), *join);
		else
			ft_basic_insert(red_basic,
				split_quote_sens(curr_c->data, i), *join);
	}
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
		red_new(curr_c, &i, red_basic, &join);
		curr_c = curr_c->next;
	}
	return (red_basic);
}

int	check_redirects(t_lexer **lex)
{
	t_lexer	*curr;

	curr = *lex;
	if (!curr)
		return (0);
	while (curr)
	{
		if ((curr->type == REDIR || curr->type == HERE) && ((curr->next
					&& !ft_strcmp(curr->next->data, "|")) || !curr->next))
			return (printf(REDIR_ERR), 0);
		if ((ft_strchr(curr->data, '>') || ft_strchr(curr->data, '<'))
			&& curr->type == STR && curr->join == 0)
		{
			if (!valid_redirects(curr->data))
				return (ft_putstr_fd(REDIR_ERR, 2), 0);
		}
		if ((curr->type == REDIR || curr->type == HERE) && curr->next
			&& (curr->next->type == REDIR || curr->next->type == HERE))
			return (ft_putstr_fd(REDIR_ERR, 2), 0);
		curr = curr->next;
	}
	return (1);
}
