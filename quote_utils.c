/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:07:01 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/09 15:00:18 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

void	clean_false_join(t_lexer **lex)
{
	t_lexer	*curr;

	curr = *lex;
	while (curr)
	{
		if (curr->join == 1)
		{
			if (!ft_strchr(curr->data, '\"') && !ft_strchr(curr->data, '\''))
				curr->join = 0;
		}
		curr = curr->next;
	}
}
