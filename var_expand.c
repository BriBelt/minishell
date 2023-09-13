/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:14:12 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/06 17:23:50 by bbeltran         ###   ########.fr       */
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
	int	loop;
	int	start;
	int	end;

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
	return (ft_substr(data, start, end - start));
}

/* Gets the amount of memory that the new node data will
 * need. */
int	total_node_len(char *data, t_shell *mini)
{
	int		i;
	int		total;
	char	*new;

	i = 0;
	total = 0;
	while (i < (int)ft_strlen(data))
	{
		new = split_variables(data, &i);
		if (ft_strchr(new, '$'))
			new = expand_envar(new, mini);
		if (new)
			total += ft_strlen(new);
	}
	return (total);
}

/* This function is only called when a "$" symbol is found
 * inside the node */
char	*found_symbol(char *data, t_shell *mini)
{
	int		i;
	char	*new;
	char	*final;

	i = 0;
	final = ft_calloc(total_node_len(data, mini), sizeof(char));
	if (!final)
		return (NULL);
	while (i < (int)ft_strlen(data))
	{
		new = split_variables(data, &i);
		if (ft_strchr(new, '$'))
			new = expand_envar(new, mini);
		if (new)
			final = ft_strjoin(final, new);
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
	int		inside;

	curr = *pipes;
	inside = 0;
	while (curr)
	{
		if (ft_strchr(curr->data, '$'))
		{
			if (curr->quote == 1)
				inside = sym_in_quotes(curr->data);
			if (!inside)
			{
				new_node = found_symbol(curr->data, mini);
				free(curr->data);
				if (new_node)
					curr->data = new_node;
			}
		}
		curr = curr->next;
	}
}
