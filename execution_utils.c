/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:37 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/13 17:06:43 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes and returns a t_pipex variable for later use during the child
 * processes.*/
t_pipex	pipex_init(void)
{
	t_pipex	pipex;

	pipex.in_fd = -1;
	pipex.out_fd = -1;
	return (pipex);
}

/* While loop that will iterate through the children_id array to make the
 * parent process wait until all the children processes are done. */
void	wait_for_child(t_pipex pipex, int count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (i < count)
	{
		waitpid(pipex.child_id[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_global.exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exit_stat = WTERMSIG(status) + 128;
	else
		g_global.exit_stat = 1;
	signal(SIGINT, signal_handler);
}
