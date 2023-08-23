/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:48:55 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 16:31:02 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_unset(char *data)
{
	if (ft_strchr(data, '='))
		return (printf("unset: %s: not a valid identifier\n", data), 0);
	if (!ft_isalpha((int)data[0]) && data[0] != '_')
		return (printf("unset: %s: not a valid identifier\n", data), 0);
	return (1);
}

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
char	**ft_unset(char **envp, t_lexer *node, int *times)
{
	char	**new_envp;
	char	**aux;
	t_lexer	*curr;

	if (node->next)
	{
		curr = node->next;
		new_envp = envp;
		while (curr)
		{
			if (check_for_unset(curr->data))
			{
				aux = new_envp;
				new_envp = get_new_envp(aux, curr->data);
				free_2D_array(aux);
			}
			curr = curr->next;
			(*times)++;
		}
		return (new_envp);
	}
	return (envp);
}
