/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:12:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/04 15:58:23 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_shell *mini, char *rd)
{
	t_basic	**basic;
	t_lexer	*curr;

	if (mini->lex)
		free_list(mini->lex);
	basic = create_basic_lst(rd);
	mini->lex = create_lexer(basic);
	def_type(mini->lex);
	clean_quotes(mini->lex);
	curr = *mini->lex;
	while (curr)
	{
		printf("Lexer: %s, index: %i, type: %i\n", curr->data, curr->index, curr->type);
		curr = curr->next;
	}
}
