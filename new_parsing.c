/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:19:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 11:16:05 by bbeltran         ###   ########.fr       */
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

/* Provisional parsing function */
t_lexer	**ft_parser(t_shell *mini, char *rd)
{
	t_basic	**space_sep;
	t_basic	**quote_sep;
	t_basic	**redirects;
	t_basic	**pipes;
	t_lexer	**lexer;
	(void)mini;

	space_sep = create_space_sep(rd);
	if (!quote_list_checker(space_sep))
		return (NULL);
	quote_sep = create_quote_sep(space_sep);
	if (!quote_list_checker(quote_sep))
		return (NULL);
	redirects = redirect_separate(quote_sep);
	pipes = pipe_separate(redirects);
	clean_false_joins(pipes);
	change_node_var(pipes, mini);
	clean_quotes(pipes);
	lexer = final_lexer(pipes);
	def_type(lexer);
	if (!check_redirects(lexer))
		return (NULL);
	if (!check_pipes(lexer))
		return (NULL);
	return (lexer);
}
