/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/31 12:01:17 by jaimmart         ###   ########.fr       */
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

void	executor(t_shell *mini)
{
	t_pipex	pipex;

	pipex = pipex_init();
	if (command_counter(mini->cmds) == 1)
	{
		if (!call_builtins(*mini->cmds, mini) && check_redir_access(mini->lex))
			only_child(pipex, *mini->cmds, mini);

	}
	else if (command_counter(mini->cmds) == 2)
	{
		if (check_redir_access(mini->lex))
		{
			pipe(pipex.pipes[0]);
			pipex = first_child(pipex, *mini->cmds, mini);
			pipex = last_child(pipex, (*mini->cmds)->next, mini);
			(close(pipex.pipes[0][0]) , close(pipex.pipes[0][1]));
		}
	}
/*	else if (command_counter(mini->cmds) == 2)
	{
		if (check_redir_access(mini->lex))
		{
			pipe(pipex.pipes);
			first_child(&pipex, *mini->cmds, mini);
			last_child(&pipex, *mini->cmds, mini);
		}
	}*/
/*	else if (command_counter(mini->cmds) == 2)
	{
		if (check_redir_access(mini->lex))
		{
			pipe(pipex.pipes);
			pipex = first_child(pipex, *mini->cmds, mini);
			last_child(pipex, (*mini->cmds)->next, mini);
			close(pipex.pipes[0]);
			close(pipex.pipes[1]);
		}
	}
	}*/
	waitpid(-1, NULL, 0);
}
