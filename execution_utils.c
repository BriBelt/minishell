/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:37 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 17:34:30 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_all_files(int in_heredocs)
{
	int		i;
	char	*name;
	char	*num;

	i = -1;
	while (++i < in_heredocs)
	{
		num = ft_itoa(i);
		name = ft_strjoin("/tmp/.heredoc_", num);
		unlink(name);
		(free(name), free(num));
	}
}

/* Initializes and returns a t_pipex variable for later use during the child
 * processes.*/
t_pipex	pipex_init(void)
{
	t_pipex	pipex;

	pipex.in_fd = -1;
	pipex.out_fd = -1;
	pipex.one_built = 0;
	return (pipex);
}

/* While loop that will iterate through the children_id array to make the
 * parent process wait until all the children processes are done. */
void	wait_for_child(t_pipex pipex, int count, t_shell *mini)
{
	int			i;
	int			status;
	t_command	*curr;

	i = 0;
	status = 0;
	curr = *mini->cmds;
	signal(SIGINT, SIG_IGN);
	while (i < count)
	{
		if (count > 0)
			waitpid(pipex.child_id[i], &status, 0);
		curr = curr->next;
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

char	**find_all_del(t_command **commands)
{
	t_command	*curr;
	t_red		*red_curr;
	char		**dels;
	int			i;

	dels = ft_calloc(here_counter(commands) + 1, sizeof(char *));
	if (!dels)
		return (NULL);
	curr = *commands;
	i = 0;
	while (curr)
	{
		red_curr = *curr->redirect;
		while (red_curr)
		{
			if (red_curr->type == HEREDOC)
			{
				dels[i] = ft_strdup(red_curr->data);
				i++;
			}
			red_curr = red_curr->next;
		}
		curr = curr->next;
	}
	return (dels);
}
