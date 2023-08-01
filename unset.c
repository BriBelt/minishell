/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:48:55 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/01 17:21:44 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Just gives the array **envp size, ignoring *desired_path. */
int	array_size(char **envp, char *desired_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], desired_path, ft_strlen(desired_path)))
			i++;
		j++;
		i++;
	}
	return (j);
}

/* Iterates through the **envp array, searching for the *desired_path, if found,
 * subtracts it from the array, returning a copy of all the **envp WITHOUT
 * the *desired_path. */
char	**get_new_envp(char **envp, char *desired_path)
{
	char	**new;
	int		i;
	int		j;

	new = ft_calloc(array_size(envp, desired_path) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], desired_path, ft_strlen(desired_path)))
		{
			new[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	return (new);
}

/* Unset builtin function, calls get_new_envp(); to create a new array of
 * the updated **envp, frees the old array **envp, and returns the
 * new array. */
char	**ft_unset(char **envp, t_lexer *node)
{
	char	**new_envp;

	if (node->next)
	{
		new_envp = get_new_envp(envp, node->next->data);
		free_2D_array(envp);
		return (new_envp);
	}
	return (envp);
}
