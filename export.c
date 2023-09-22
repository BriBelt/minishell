/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:29:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 18:43:20 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_export(char *data)
{
	int	i;

	i = -1;
	while (data[++i] && data[i] != '=')
	{
		if (!ft_isalnum(data[i]))
		{
			g_global.exit_stat = 1;
			return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
		}
	}
	if (!ft_isalpha((int)data[0]) && data[0] != '_')
	{
		g_global.exit_stat = 1;
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	}
	if (!ft_strchr(data, '='))
		return (2);
	return (1);
}

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
		if (!ft_strncmp(envp[i], new_var, len))
		{
			if (envp[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

/* Iterates through the **envp array while copies it into a **new array, when
 * it reaches the end of the **envp, adds the *new_var into **new array. */
char	**export_new_envar(char **envp, char *new_var)
{
	char	**new;
	int		found;
	int		i;
	int		j;
	int		array_size;

	found = found_var(envp, new_var);
	array_size = find_size_envp(envp);
	if (found == -1)
		array_size++;
	new = ft_calloc(array_size + 1, sizeof(char *));
	if (!new)
		return (NULL);
	j = 0;
	i = -1;
	while (++i < array_size)
	{
		if (i == found)
			new[i] = ft_strdup(new_var);
		else if (found == -1 && i == array_size - 1)
			new[i] = ft_strdup(new_var);
		else if (envp[j])
			new[i] = ft_strdup(envp[j++]);
	}
	return (new);
}

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
					return (new_envp = return_new_envp(new_envp, i, curr));
			}
		}
	}
	else
		print_sort_env(envp);
	return (envp);
}
