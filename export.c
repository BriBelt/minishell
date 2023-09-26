/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:29:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 16:10:10 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the index of the **envp that is the same string as the *new_var
 * or returns the end of the **envp index if not found. */
int	found_var(char **envp, char *new_var)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (new_var[len] && new_var[len] != '=')
		len++;
	while (envp[i])
	{
		if (envp[i] && !ft_strncmp(envp[i], new_var, len))
		{
			if (envp[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**where_to_insert(char **envp, char **new, char *new_var, int a_size)
{
	int		i;
	int		j;
	int		found;

	i = -1;
	j = 0;
	found = found_var(envp, new_var);
	while (++i < a_size)
	{
		if (i == found)
		{
			new[i] = ft_strdup(new_var);
			j++;
		}
		else if (found == -1 && i == a_size - 1)
			new[i] = ft_strdup(new_var);
		else if (envp[j])
			new[i] = ft_strdup(envp[j++]);
	}
	return (new);
}

/* Iterates through the **envp array while copies it into a **new array, when
 * it reaches the end of the **envp, adds the *new_var into **new array. */
char	**export_new_envar(char **envp, char *new_var)
{
	char	**new;
	int		array_size;
	int		found;

	found = found_var(envp, new_var);
	array_size = find_size_envp(envp, found);
	new = ft_calloc(array_size + 1, sizeof(char *));
	if (!new)
		return (NULL);
	new = where_to_insert(envp, new, new_var, array_size);
	return (new);
}

/* Part of ft_export function that we had to cut because of norminette.
 * Takes the old value of new_envp, stores it in aux, calls the
 * export_new_envar(); function, sets a new value to new_envp and frees
 * the aux variable. */
char	**return_new_envp(char **new_envp, int i, t_command *curr)
{
	char	**aux;

	aux = new_envp;
	new_envp = export_new_envar(aux, curr->args[i]);
	free_2d_array(aux);
	return (new_envp);
}

/* Export builtin function, calls export_new_envar(); that creates a new array
 * of the updated **envp (with the new variable), frees the old array **envp,
 * and returns the new array. */
char	**ft_export(char **envp, t_command *node)
{
	char		**new_envp;
	t_command	*curr;
	int			i;
	int			result;

	i = 0;
	curr = node;
	new_envp = NULL;
	if (curr->args[1])
	{
		new_envp = envp;
		while (curr->args[++i])
		{
			result = check_for_export(curr->args[i]);
			if (result)
			{
				g_global.exit_stat = 0;
				if (result == 1)
					new_envp = return_new_envp(new_envp, i, curr);
			}
		}
	}
	else
		print_sort_env(envp);
	return (new_envp);
}
