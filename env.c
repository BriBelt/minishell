/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:39:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 17:47:08 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Env builtin function, iterates through the given **envp and prints each
 * *envp. */
void	ft_env(t_command *node, char **envp)
{
	int	i;

	if (node->args[1])
	{
		g_global.exit_stat = 127;
		ft_putstr_fd("env: Takes no arguments\n", 2);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	g_global.exit_stat = 0;
}
