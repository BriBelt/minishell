/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/29 18:12:30 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_init(t_pipex *pipex, t_command **commands)
{
	pipex->child_id = 0;
	(void)commands;
//	pipex->pipes = malloc(command_counter(commands) - 1 * sizeof(int));
//	if (!pipex->pipes)
//		return ;
	pipex->in_fd = 0;
	pipex->out_fd = 0;
}

void	executor(t_shell *mini)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return ;
	pipex_init(pipex, mini->cmds);
	if (command_counter(mini->cmds) == 1)
	{
		if (!call_builtins(*mini->cmds, mini) && check_redir_access(mini->lex))
				only_child(pipex, *mini->cmds, mini);
	}
	else if (command_counter(mini->cmds) == 2)
	{
//		create_pipes(mini->cmds, pipex);
		pipe(pipex->pipes);
		first_child(pipex, *mini->cmds, mini);
		last_child(pipex, (*mini->cmds)->next, mini);
	}
	waitpid(-1, NULL, 0);
}
