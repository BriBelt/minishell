/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:12:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/08 17:51:55 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_shell *mini, char *rd)
{
	t_basic	**basic;
	t_basic	**r_basic;
	t_basic	**p_basic;
	t_lexer	*curr;
//	t_basic	*curr;

	basic = create_basic_lst(rd);
	r_basic = redirect_separate(basic);
	free_t_basic(basic);
	p_basic = pipe_separate(r_basic);
	free_t_basic(r_basic);
	mini->lex = create_lexer(p_basic);
	free_t_basic(p_basic);
	def_type(mini->lex);
	if (!check_redirects(mini->lex) || !check_pipes(mini->lex))
		free_t_lexer(mini->lex);
	clean_quotes(mini->lex);
	curr = *mini->lex;
//	curr = *basic;
//	curr = *r_basic;
	while (curr)
	{
		printf("Lexer: %s, index: %i, type: %i\n", curr->data, curr->index, curr->type);
//		printf("Lexer: %s\n", curr->data);
		curr = curr->next;
	}
}
