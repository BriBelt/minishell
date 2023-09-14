/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:03:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/14 14:01:37 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cd builtin function, checks if the node->next of the given node exists if it
 * does exist, calls chdir(); with the node->next->data(desired destination)
 * to move to that directory, if the directory does not exist or doesn't 
 * have the correct permissions, returns an error message. */
void	ft_cd(t_command *node)
{
	if (node->args[1])
	{
		if (chdir(node->args[1]) == -1)
		{
			g_global.exit_stat = 1;
			perror("cd");
		}
		else
		{
//			if (g_global.pwd)
//				free(g_global.pwd);
			g_global.exit_stat = 0;
			g_global.pwd = getcwd(NULL, 0);
		}
	}
	else
	{
//		if (g_global.pwd)
//			free(g_global.pwd);
		g_global.exit_stat = 0;
		chdir("~");
		g_global.pwd = getcwd(NULL, 0);
	}
}
