/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:23:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/01 15:22:26 by bbeltran         ###   ########.fr       */
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
