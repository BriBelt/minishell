/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:28:50 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 14:45:47 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_size_envp(char **envp, int found)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	if (found == -1)
		size++;
	return (size);
}

/* This function checks the node->args[data] given, to check for syntax errors,
 * such as non-alphanumeric characters inside the data or the first character
 * is not a letter. Returns 0 if the data does not accomplish the requirements,
 * a 1 if everything is fine, and a 2 if there's no equal sign. */
int	check_for_export(char *data)
{
	int	i;

	i = -1;
	while (data[++i] && data[i] != '=')
	{
		if (!ft_isalnum(data[i]) && data[i] != '_')
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
