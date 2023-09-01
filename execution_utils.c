/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:37 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/01 15:13:22 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	pipex_init(void)
{
	t_pipex	pipex;

	pipex.in_fd = -1;
	pipex.out_fd = -1;
	return (pipex);
}

/*void	close_pipes(t_pipex pipex, int count)
{
	int i;
	i = 0;
	while (i < count)
	{
		close(pipex.pipes[i][0]);
		close(pipex.pipes[i][1]);
	}

}*/
void	wait_for_child(t_pipex pipex, int count)
{
	int	i;

	i = 0;
	while (pipex.child_id[i] && i < count)
	{
		waitpid(pipex.child_id[i], NULL, 0);
		i++;
	}
}
