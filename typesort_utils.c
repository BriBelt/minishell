/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:23:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 17:48:54 by bbeltran         ###   ########.fr       */
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

/* Returns the array (char **) of the sent *pathname. */
char	**get_paths(char *pathname)
{
	char	**paths;
	char	*whole;

	whole = getenv(pathname);
	paths = ft_split(whole, ':');
	return (paths);
}

/* Returns the expanded value of the environment variable given by 
 * getenv(); if it exist, otherwise returns NULL.
 * ONLY FOR lst->type = VAR */
char	*expand_envar(char *data)
{
	char	*expanded;
	char	*clean_data;
	int		len;

	len = ft_strlen(data) - 1;
	clean_data = ft_substr(data, 1, len);
	expanded = getenv(clean_data);
	free(clean_data);
	free(data);
	return (expanded);
}
