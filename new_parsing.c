/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:19:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 16:00:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_basic	*curr;
	int		single;
	int		double_q;

	curr = *pipes;
	while (curr)
	{
		curr->quote = 0;
		single = 0;
		double_q = 0;
		if (ft_strchr(curr->data, '\''))
			single = ft_strlen(ft_strchr(curr->data, '\''));
		if (ft_strchr(curr->data, '\"'))
			double_q = ft_strlen(ft_strchr(curr->data, '\"'));
		if (single < double_q)
			curr->quote = 2;
		else if (double_q < single)
			curr->quote = 1;
		if (redirect_or_pipe(curr->data))
			curr->join = 0;
		curr = curr->next;
	}
}

t_basic	**last_basic(t_shell *mini, char *rd)
{
	t_basic	**space_sep;
	t_basic	**quote_sep;
	t_basic	**redirects;
	t_basic	**pipes;

	space_sep = create_space_sep(rd);
	if ((space_sep && !quote_list_checker(space_sep)) || !space_sep)
	{
		if (space_sep)
			free_t_basic(space_sep);
		return (g_global.exit_stat = 1, NULL);
	}
	quote_sep = create_quote_sep(space_sep);
	free_t_basic(space_sep);
	if ((quote_sep && !quote_list_checker(quote_sep)) || !quote_sep)
	{
		if (quote_sep)
			free_t_basic(quote_sep);
		return (g_global.exit_stat = 1, NULL);
	}
	redirects = redirect_separate(quote_sep);
	free_t_basic(quote_sep);
	pipes = pipe_separate(redirects);
	(free_t_basic(redirects), clean_false_joins(pipes));
	return (change_node_var(pipes, mini), clean_quotes(pipes), pipes);
}

t_lexer	**ft_parser(t_shell *mini, char *rd)
{
	t_basic	**final_basic;
	t_lexer	**lexer;

	final_basic = last_basic(mini, rd);
	lexer = final_lexer(final_basic);
	(def_type(lexer), free_t_basic(final_basic));
	if ((lexer && (!check_redirects(lexer) || !check_pipes(lexer))) || !lexer)
		return (free_t_lexer(lexer), g_global.exit_stat = 258, NULL);
	return (lexer);
}
