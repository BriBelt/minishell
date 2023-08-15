/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:19:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/15 16:50:02 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Provisional initialize_t_quote function */
t_quote	*initialize_t_quote(void)
{
	t_quote	*handle;

	handle = malloc(sizeof(t_quote));
	handle->normal = 1;
	handle->count = 0;
	handle->start = -1;
	handle->end = 0;
	handle->first = 0;
	return (handle);
}

/* Provisional create_node function */
t_basic	*new_create_node(char *content, int join)
{
	t_basic	*node;

	node = malloc(sizeof(t_basic));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	node->join = join;
	return (node);
}

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
	int		i;
	int		rd_len;

	i = 0;
	space_sep = malloc(sizeof(t_basic *));
	if (!space_sep)
		return (NULL);
	*space_sep = NULL;
	rd_len = ft_strlen(rd);
	while (i < rd_len)
		ft_basic_insert(space_sep, space_split(rd, &i), 0);
	return (space_sep);
}

/*
 *				 QUOTE SEPARATION					
 *  											*/
/* This function splits the given *data by the first type of
 * quotes found inside the *data, returns a new string that
 * will later be used by our ft_basic_insert();. */
char	*quote_split(char *rd, int *i)
{
	t_quote	*h;

	h = initialize_t_quote();
	while (rd[*i])
	{
		if (quote_type(rd[*i]))
		{
			h->normal = 0;
			if (!h->first)
				h->first = quote_type(rd[*i]);
			if (quote_type(rd[*i]) == h->first)
				h->count++;
		}
		if (h->count == 2)
		{
			h->end = (*i) + 1;
			(*i)++;
			break ;
		}
		if (h->normal && h->start == -1)
			h->start = *i;
		else if (h->count == 1 && h->first && h->start == -1)
			h->start = *i;
		(*i)++;
	}
	return (ft_substr(rd, h->start, h->end - h->start));
}

/* Just checks if there's a quote inside the *data. */
int	quote_inside_node(char *data)
{
	if (ft_strchr(data, '\'') || ft_strchr(data, '\"'))
		return (1);
	return (0);
}

/* Creates a new **t_basic going through each node of the
 * given **space_sep list, if the node->data has quotes
 * it calls quote_split();, assigning the join value, by default
 * is 1, but as the function ft_basic_insert(); keeps being called
 * the value of join increments. If there's no quotes in 
 * the node->data, it does a simple ft_basic_insert(); of the node.*/
t_basic	**create_quote_sep(t_basic **space_sep)
{
	t_basic **quote_sep;
	t_basic *curr_space;
	size_t	join;
	int		i;

	quote_sep = malloc(sizeof(t_basic *));
	if (!quote_sep)
		return (NULL);
	*quote_sep = NULL;
	curr_space = *space_sep;
	while (curr_space)
	{
		i = 0;
		join = 0;
		if (quote_inside_node(curr_space->data))
		{
			while (i < (int)ft_strlen(curr_space->data))
				ft_basic_insert(quote_sep, quote_split(curr_space->data, &i), ++join);
		}
		else if (!quote_inside_node(curr_space->data))
			ft_basic_insert(quote_sep, curr_space->data, 0);
		curr_space = curr_space->next;
	}
	return (quote_sep);
}

/*
 *				IDENTIFY JOIN NODES
 *  											*/
/* Iterates the whole **list, checking each node->content for
 * quotes, depending on the type sets curr->quote to the value
 * of the quote found. It also checks if the node->data is actually
 * a pipe or a redirection, if it is, sets the curr->join value
 * to 0. */
void	clean_false_joins(t_basic **pipes)
{
	t_basic *curr;

	curr = *pipes;
	while (curr)
	{
		if (ft_strchr(curr->data, '\''))
			curr->quote = 1;
		else if (ft_strchr(curr->data, '\"'))
			curr->quote = 2;
		else
			curr->quote = 0;
		if (redirect_or_pipe(curr->data))
			curr->join = 0;
		curr = curr->next;
	}
}

/*
 *				VARIABLES	
 *  										*/
/* Splits the given node->data depending on if it finds a "$"
 * if */
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

/* Will only be called if the node->data has a "$". 
 * If node->quote = 0 or 2, takes the data and copies anything
 * that is before the symbol, stores it into *previous. Next,
 * takes the variable name (including the symbol) and calls
 * expand_envar();. */
/*void	variable_node_edit(char *data)
{
	char	*rest;
	char	*var;
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (data[++i] && data[i] != '$')
		rest[i] = data[i];	
	rest[i] = '\0';
	while (data[i++] && !quote_type(data[i]))
	{
		var[j] = data[i];
		j++;
	}

}*/
/* This function manages $VARs, iterates the **list, checks each
 * node->content for a $ character, if is not found, does nothing
 * else if the character is found, checks what the node->quote is.
 * If node->quote is 2 or 0, expands the variable if it exists.
 * Else if node->quote is 1, the node->data does not change. */ 
/*void	variable_management(t_basic **pipes)
{
	t_basic	*curr;

	curr = *pipes;
	while (curr)
	{
		if (ft_strchr(curr->data, '$'))
	}
}*/
/*t_basic	**create_final_list(t_basic **pipes)
{
	t_basic	**final_b;
	t_basic *curr;

	final_b = malloc(sizeof(t_basic *));
	if (!final_b)
		return (NULL);
	*final_b = NULL;
	curr = *pipes;

}*/
/* Provisional parsing function */
/*void	ft_parser(t_shell *mini, char *rd)
{
	t_basic	**space_sep;
	t_basic	**redirects;
	t_basic	**pipes;
	t_basic	**quote_sep;
	t_basic	*curr;

	(void)mini;
	space_sep = create_space_sep(rd);
	quote_sep = create_quote_sep(space_sep);
	redirects = redirect_separate(quote_sep);
	pipes = pipe_separate(redirects);
	clean_false_joins(pipes);
	curr = *pipes;

	while (curr)
	{
		printf("Basic: %s join: %zu quote: %zu\n", curr->data, curr->join, curr->quote);
		curr = curr->next;
	}
	
}*/
int	main(void)
{
	char	*str;
	int		i;

//	str = "<< |\"\'hola\'\"hello !";
	str = "hello$PATH$HOME\'hi\'";
	i = 0;
	while (str[i])
		printf("new:%s\n", split_variables(str, &i));
	return (0);
}
