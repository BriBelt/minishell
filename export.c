/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:29:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/28 12:55:02 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_export(char *data)
{
	if (!ft_isalpha((int)data[0]) && data[0] != '_')
		return (printf("unset: %s: not a valid identifier\n", data), 0);
	if (!ft_strchr(data, '='))
		return (0);
	return (1);
}

/* Returns the index of the **envp that is the same string as the *new_var
 * or returns the end of the **envp index if not found. */
int	found_var(char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], new_var, ft_strlen(new_var)))
			return (i);
		i++;
	}
	return (i);
}

/* Iterates through the **envp array while copies it into a **new array, when
 * it reaches the end of the **envp, adds the *new_var into **new array. */
char	**export_new_envar(char **envp, char *new_var)
{
	char	**new;
	int		i;
	int		j;

	i = found_var(envp, new_var);
	j = 0;
	while (envp[j])
		j++;
	if (i == j)
		new = ft_calloc(++i + 1, sizeof(char *));
	else
		new = ft_calloc(j + 1, sizeof(char *));
	if (!new)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		if (j == i - 1)
			new[j] = ft_strdup(new_var);
		else
			new[j] = ft_strdup(envp[j]);
	}
	return (new);
}

/* Export builtin function, calls export_new_envar(); that creates a new array
 * of the updated **envp (with the new variable), frees the old array **envp,
 * and returns the new array. */
char	**ft_export(char **envp, t_command *node)
{
	char		**new_envp;
	char		**aux;
	t_command	*curr;
	int			i;

	i = 1;
	curr = node;
	if (curr->args[i])
	{
		new_envp = envp;
		while (curr->args[i])
		{
			if (check_for_export(curr->args[i]))
			{
				aux = new_envp;
				new_envp = export_new_envar(aux, curr->args[i]);
				free_2D_array(aux);
			}
			i++;
		}
		return (new_envp);
	}
	else
		print_sort_env(envp);
	return (envp);
}
