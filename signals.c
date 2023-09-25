/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:56:56 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 16:14:48 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_signal(int here_child)
{
	int	status;
	int	exited;

	exited = 0;
	(signal(SIGINT, SIG_IGN), waitpid(here_child, &status, 0));
	if (WIFEXITED(status))
		g_global.exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exited = 1;
		g_global.exit_stat = 1;
	}
	else
		g_global.exit_stat = 0;
	signal(SIGINT, signal_handler);
	return (exited);
}	

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_global.exit_stat = 1;
}
