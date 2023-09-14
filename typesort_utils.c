/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:23:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/14 15:52:28 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Differentiates between FLAG or VAR type, else
 * is a STR type. */
int	flag_or_envar(char *content)
{
	if (!ft_strncmp(content, "-", 1))
		return (FLAG);
	if (!ft_strncmp(content, "$", 1))
		return (VAR);
	return (STR);
}

/* Checks if *content is a FIL (file) type, else
 * is definetly a STR type. */
int	is_file(char *content)
{
	if (!access(content, F_OK | R_OK))
		return (FIL);
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
		if (curr->next && valid_characters(curr->next->data))
		{
			if (curr->type == REDIR && curr->next)
				curr->next->type = FIL;
			if (curr->type == HERE && curr->next)
				curr->next->type = DEL;
			curr = curr->next;
		}
		else
		{
			g_global.exit_stat = 1;
			return ;
		}
	}
}
