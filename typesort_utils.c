/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:23:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 13:05:39 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Differentiates between FLAG or VAR type, else
 * is a STR type. */
int	flag_or_envar(char *content, int quote_type)
{
	if (!ft_strncmp(content, "-", 1))
		return (FLAG);
	if (!ft_strncmp(content, "$", 1) && quote_type != 1)
		return (VAR);
	return (STR);
}

int	valid_characters(char *content)
{
	if (!content)
		return (0);
	if (!ft_strcmp(content, "|"))
		return (0);
	if (!ft_strcmp(content, "<") || !ft_strcmp(content, ">"))
		return (0);
	return (1);
}

void	is_file_type(t_lexer **lexer)
{
	t_lexer	*curr;

	curr = *lexer;
	while (curr)
	{
		if ((curr->type == HERE || curr->type == REDIR) && curr->next)
		{
			if (!valid_characters(curr->next->data))
			{
				g_global.exit_stat = 1;
				return ;
			}
			else
			{
				if (curr->type == REDIR && curr->next)
					curr->next->type = FIL;
				if (curr->type == HERE && curr->next)
					curr->next->type = DEL;
			}
		}
		curr = curr->next;
	}
}
