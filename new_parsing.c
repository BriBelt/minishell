/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:19:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 16:19:47 by bbeltran         ###   ########.fr       */
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

/* Provisional parsing function */
t_lexer	**ft_parser(t_shell *mini, char *rd)
{
	t_basic	**space_sep;
	t_basic	**quote_sep;
	t_basic	**redirects;
	t_basic	**pipes;
	t_lexer	**lexer;

	space_sep = create_space_sep(rd);
	lexer = NULL;
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
	free_t_basic(redirects);
	clean_false_joins(pipes);
	change_node_var(pipes, mini);
	clean_quotes(pipes);
	lexer = final_lexer(pipes);
	def_type(lexer);
	free_t_basic(pipes);
	if ((lexer && (!check_redirects(lexer) || !check_pipes(lexer))) || !lexer)
		return (free_t_lexer(lexer), g_global.exit_stat = 258, NULL);
	return (lexer);
}
