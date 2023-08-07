/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:12:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/07 14:32:31 by jaimmart32       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_shell *mini, char *rd)
{
	t_basic	**basic;
	t_basic	**red_basic;
	t_lexer	*curr;

	if (mini->lex)
		free_list(mini->lex);
	basic = create_basic_lst(rd);
	red_basic = redirec_separate(basic);
	mini->lex = create_lexer(red_basic);
	def_type(mini->lex);
	clean_quotes(mini->lex);
	curr = *mini->lex;
	while (curr)
	{
		printf("Lexer: %s, index: %i, type: %i\n", curr->data, curr->index, curr->type);
		curr = curr->next;
	}
}
