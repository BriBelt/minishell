/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:19:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 16:19:04 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


/*t_lexer	**final_lexer(t_basic **lst)
{
	t_lexer	**lexer;
	t_basic	*curr;
	char	*data;
	size_t	times;
	size_t	i;
	size_t	quote;
	int		n;

	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (NULL);
	*lexer = NULL;
	n = 0;
	curr = *lst;
	while (curr)
	{
		if (curr->join == 1)
		{
			i = 0;
			data = ft_calloc(join_len(curr) + 1, sizeof(char));
			times = join_times(curr);
			quote = curr->quote;
			while (++i <= times)
			{
				data = ft_strjoin(data, curr->data);
				curr = curr->next;
			}
		}
		else
		{
			data = curr->data;
			quote = curr->quote;
			curr = curr->next;
		}
		ft_lexer_insert(lexer, data, n++, quote);
	}
	return (lexer);
}*/
/* Provisional parsing function */
void	ft_parser(t_shell *mini, char *rd)
{
	t_basic	**space_sep;
	t_basic	**quote_sep;
	t_basic	**redirects;
	t_basic	**pipes;
//	t_basic	*curr;
	t_lexer	*curr;
	t_lexer	**lexer;
	(void)mini;

	space_sep = create_space_sep(rd);
	if (!quote_list_checker(space_sep))
		return ;
	quote_sep = create_quote_sep(space_sep);
	if (!quote_list_checker(quote_sep))
		return ;
	redirects = redirect_separate(quote_sep);
	pipes = pipe_separate(redirects);
	clean_false_joins(pipes);
	change_node_var(pipes, mini);
	clean_quotes(pipes);
	lexer = final_lexer(pipes);
//	printf("new join: %i\n", new_joined_len(pipes));
	curr = *lexer;
//	curr = *pipes;
	while (curr)
	{
		printf("Lex Node: %s, index: %i, join: %zu\n", curr->data, curr->index, curr->join);
//		printf("Basic: %s join: %zu quote: %zu\n", curr->data, curr->join, curr->quote);
		curr = curr->next;
	}
}
