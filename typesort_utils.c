/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:23:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/26 13:43:22 by bbeltran         ###   ########.fr       */
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

void	is_file_type(t_lexer **lexer)
{
	t_lexer	*curr;

	curr = *lexer;
	while (curr)
	{
		if (curr->type == REDIR && curr->next)
			curr->next->type = FIL;
		curr = curr->next;
	}
}
