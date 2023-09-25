/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:14:12 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 17:45:19 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_final_str(t_exvar *ex, t_shell *mini)
{
	if (ft_strchr(ex->aux, '$'))
	{
		ex->expanded = expand_envar(ex->aux, mini);
		free(ex->aux);
		ex->aux = ex->final_str;
		if (ex->expanded)
		{
			ex->final_str = ft_strjoin(ex->final_str, ex->expanded);
			(free(ex->expanded), free(ex->aux));
		}
	}
	else if (!ft_strchr(ex->aux, '$'))
	{
		ex->no_sym = ft_strdup(ex->aux);
		free(ex->aux);
		ex->aux = ex->final_str;
		ex->final_str = ft_strjoin(ex->final_str, ex->no_sym);
		(free(ex->aux), free(ex->no_sym));
	}
	else
		ex->final_str = NULL;
}

char	*found_symbol(char *data, t_shell *mini)
{
	int		i;
	t_exvar	ex;

	ex.expanded = NULL;
	ex.no_sym = NULL;
	ex.final_str = ft_calloc(1, sizeof(char));
	if (!ex.final_str)
		return (NULL);
	i = 0;
	while (i < (int)ft_strlen(data))
	{
		ex.aux = split_variables(data, &i);
		set_final_str(&ex, mini);
	}
	return (ex.final_str);
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
		set_first_quote2(data, &count, &first, &i);
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

char	*expand_method(int *count, t_basic *curr, char *new_node, t_shell *mini)
{
	if (*count > 1 && curr->quote == 1)
		new_node = more_than_one_expand(curr->data, mini);
	else
		new_node = found_symbol(curr->data, mini);
	return (new_node);
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
				new_node = expand_method(&count, curr, new_node, mini);
				aux = curr->data;
				curr->data = new_node;
				free(aux);
			}
		}
		curr = curr->next;
	}
}
