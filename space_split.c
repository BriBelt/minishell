/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:11:03 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 17:42:13 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* As its name says so, ignores the spaces found at the beginning of the *rd*/
void	ft_ignore_spaces(char *rd, int *i)
{
	while (rd[*i] && rd[*i] == ' ')
		(*i)++;
}

/* Just to cut spaces at the end of the *rd. */
int	cut_end_spaces(char *rd)
{
	int	end;

	end = ft_strlen(rd);
	while (rd[end] == ' ')
		end--;
	return (end);
}

/* Needed function to set variables when a quote character is found. */
void	found_quotes_rd(char c, int *normal, int *count)
{
	if (quote_type(c))
	{
		*normal = 0;
		(*count)++;
	}
	if (*count == 2)
	{
		*count = 0;
		*normal = 1;
	}
}

/* Generates a new *str from the *rd, which is a space-separated
 * string. Only separates by spaces if those spaces are NOT inside
 * a quoted sentence. */
char	*space_split(char *rd, int *i)
{
	int	start;
	int	normal;
	int	end;
	int	count;

	ft_ignore_spaces(rd, i);
	start = *i;
	end = -1;
	normal = 1;
	count = 0;
	while (rd[*i] && end == -1)
	{
		found_quotes_rd(rd[*i], &normal, &count);
		if (normal && rd[*i] == ' ')
			end = *i;
		(*i)++;
	}
	if (end == -1)
		end = *i;
	return (ft_substr(rd, start, end - start));
}

/* This function creates a t_basic list of the space-separated
 * *rd. It sets the space_sep->join = 0 if it's a non-quoted
 * string or space_sep->join = 1 if it is quoted. */
t_basic	**create_space_sep(char *rd)
{
	t_basic	**space_sep;
	char	*new;
	int		i;
	int		rd_len;

	i = 0;
	space_sep = malloc(sizeof(t_basic *));
	if (!space_sep)
		return (NULL);
	*space_sep = NULL;
	rd_len = ft_strlen(rd);
	while (i < rd_len)
	{
		new = space_split(rd, &i);
		if (new)
			ft_basic_insert(space_sep, new, 0);
	}
	return (space_sep);
}
