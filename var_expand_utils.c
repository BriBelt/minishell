/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:50:33 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 16:56:39 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_first_quote2(char *data, int *count, int *first, int *i)
{
	if (data[*i] == '\'')
	{
		(*count)++;
		if (*first == -1)
			*first = *i;
	}
}

/* Splits the given node->data depending on if it finds a "$"
 * or quotes. Returns the result of the cutted *data. */
char	*split_variables(char *data, int *i)
{
	int		loop;
	int		start;
	int		end;
	char	*new;

	start = *i;
	end = -1;
	loop = 0;
	while (data[*i] && data[*i] != '$' && !quote_type(data[*i]))
	{
		loop = 1;
		(*i)++;
	}
	while (!loop && data[*i] && end == -1)
	{
		if (quote_type(data[*i]) && start != *i)
			break ;
		if (data[*i] == '$' && start != *i)
			break ;
		(*i)++;
	}
	if (end == -1)
		end = *i;
	new = ft_substr(data, start, end - start);
	return (new);
}

/* Gets the amount of memory that the new node data will
 * need. */
int	total_node_len(char *data, t_shell *mini)
{
	int		i;
	int		total;
	char	*new;
	char	*aux;

	i = 0;
	total = 0;
	while (i < (int)ft_strlen(data))
	{
		new = split_variables(data, &i);
		if (ft_strchr(new, '$'))
		{
			aux = new;
			new = expand_envar(aux, mini);
			free(aux);
		}
		if (new)
			total += ft_strlen(new);
	}
	return (total);
}

int	symbol_count(char *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data[++i])
	{
		if (data[i] == '$')
			count++;
	}
	return (count);
}

char	*more_than_one_expand(char *data, t_shell *mini)
{
	char	*quoted_str;
	char	*str_expand;
	char	*expanded;
	char	*new;

	quoted_str = ft_strdup(ft_strchr(data, '\''));
	str_expand = ft_substr(data, 0, ft_strlen(data) - ft_strlen(quoted_str));
	expanded = found_symbol(str_expand, mini);
	new = ft_strjoin(expanded, quoted_str);
	(free(expanded), free(str_expand), free(quoted_str));
	return (new);
}
