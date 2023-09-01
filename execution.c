/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/01 15:15:50 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	execute_one(t_shell *mini, t_pipex pipex)
{
	if (!call_builtins(*mini->cmds, mini) && check_redir_access(mini->lex))
		only_child(pipex, *mini->cmds, mini);
	return (pipex);
}

t_pipex	execute_two(t_shell *mini, t_pipex pipex)
{
	if (check_redir_access(mini->lex))
	{
		pipe(pipex.pipes[0]);
		pipex = first_child(pipex, *mini->cmds, mini);
		pipex = last_child(pipex, (*mini->cmds)->next, mini, 1);
		(close(pipex.pipes[0][0]) , close(pipex.pipes[0][1]));
	}
	return (pipex);
}

t_pipex	execute_all(t_shell *mini, t_pipex pipex, int count)
{
	t_command	*cmd;
	int			i;

	if (check_redir_access(mini->lex))
	{
		cmd = *mini->cmds;
		i = 0;
		while (i < count && cmd)
		{
			if (i != count - 1)
				pipe(pipex.pipes[i]);
			if (i == 0)
				pipex = first_child(pipex, cmd, mini);
			else if (i == count - 1)
			{
				close(pipex.pipes[i - 1][1]);
				pipex = last_child(pipex, cmd, mini, i);
			}
			else if (i < 0 && i < count - 1)
				pipex = middle_child(pipex, cmd, mini, i);
			i++;
			cmd = cmd->next;
		}
	}
	return (pipex);
}

void	executor(t_shell *mini)
{
	t_pipex		pipex;
	int			count;

	pipex = pipex_init();
	count = command_counter(mini->cmds);
	if (count == 1)
		pipex = execute_one(mini, pipex);
	else if (count == 2)
		pipex = execute_two(mini, pipex);
	else
		pipex = execute_all(mini, pipex, count);
//	wait_for_child(pipex, count);
	waitpid(pipex.child_id[0], NULL, 0);
	waitpid(pipex.child_id[1], NULL, 0);
	waitpid(pipex.child_id[2], NULL, 0);
//	waitpid(-1, NULL, 0);
}
