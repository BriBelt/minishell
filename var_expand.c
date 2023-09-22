/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:14:12 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 12:27:02 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *				VARIABLES	
 *  										*/
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

char	*found_symbol(char *data, t_shell *mini)
{
	int		i;
	char	*expanded;
	char	*final;
	char	*no_sym;
	char	*aux;

	final = ft_calloc(1, sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (i < (int)ft_strlen(data))
	{
		aux = split_variables(data, &i);
		if (ft_strchr(aux, '$'))
		{
			expanded = expand_envar(aux, mini);
			free(aux);
			aux = final;
			if (expanded)
			{
				final = ft_strjoin(final, expanded);
				(free(expanded), free(aux));
			}
		}
		else if (!ft_strchr(aux, '$'))
		{
			no_sym = ft_strdup(aux);
			free(aux);
			aux = final;
			final = ft_strjoin(final, no_sym);
			(free(aux), free(no_sym));
		}
		else
			final = NULL;
	}
	return (final);
}

/* This function is only called when there's a node with
 * single quotes. It checks the *data, looks for the first
 * and last occurence of a single quote, next looks for the
 * occurence of a $ symbol. Finally, it compares if the
 * symbol position is greater than the first single quote
 * and smaller than the last quote position. If it is,
 * returns a 1, meaning that the variable is inside single
 * quotes, therefore it won't be expanded. */
int	sym_in_quotes(char *data)
{
	int	first;
	int	i;
	int	last;
	int	count;
	int	symbol;

	first = -1;
	last = -1;
	symbol = 0;
	count = 0;
	i = 0;
	while (data[i] && last == -1)
	{
		if (data[i] == '\'')
		{
			count++;
			if (first == -1)
				first = i;
		}
		if (count == 2)
			last = i;
		i++;
	}
	while (data[symbol] != '$')
		symbol++;
	if (symbol > first && symbol < last)
		return (1);
	return (0);
}

/* Checks the **pipes list, if the node contains a $
 * symbol, if it does, checks if the node->quote is 
 * 1, calls sym_in_quotes();. If the result of that
 * function is 0, calls found_symbol(); and sets
 * the new value of curr->data as the new expanded 
 * node. */
void	change_node_var(t_basic **pipes, t_shell *mini)
{
	t_basic	*curr;
	char	*new_node;
	char	*aux;
	int		inside;
	int		count;

	curr = *pipes;
	inside = 0;
	while (curr)
	{
		if (ft_strchr(curr->data, '$'))
		{
			count = symbol_count(curr->data);
			if (curr->quote == 1)
				inside = sym_in_quotes(curr->data);
			if (!inside || curr->quote != 1)
			{
				if (count > 1 && curr->quote == 1)
					new_node = more_than_one_expand(curr->data, mini);
				else
					new_node = found_symbol(curr->data, mini);
				aux = curr->data;
				curr->data = new_node;
				free(aux);
			}
		}
		curr = curr->next;
	}
}
