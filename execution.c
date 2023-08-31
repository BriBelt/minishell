/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:26:35 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/31 14:26:00 by bbeltran         ###   ########.fr       */
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

void	executor(t_shell *mini)
{
	t_pipex		pipex;
	t_command	*cmd;
	int			i;
	int			count;

	pipex = pipex_init();
	count = command_counter(mini->cmds);
	if (count == 1)
	{
		if (!call_builtins(*mini->cmds, mini) && check_redir_access(mini->lex))
			only_child(pipex, *mini->cmds, mini);
	}
	else if (count == 2)
	{
		if (check_redir_access(mini->lex))
		{
			pipe(pipex.pipes[0]);
			pipex = first_child(pipex, *mini->cmds, mini);
			pipex = last_child(pipex, (*mini->cmds)->next, mini, 1);
			(close(pipex.pipes[0][0]) , close(pipex.pipes[0][1]));
		}
	}
	else
	{
		if (check_redir_access(mini->lex))
		{
			cmd = *mini->cmds;
			i = 0;
			while (i < count && cmd)
			{
				int j = 0;
				while (cmd->args[j])
				{
					printf("cmd[%i] = %s\n", j, cmd->args[j]);
					j++;
				}
				pipe(pipex.pipes[i]);
				if (i == 0)
					pipex = first_child(pipex, cmd, mini);
				else if (i == count - 1)
					pipex = last_child(pipex, cmd, mini, i);
				else
					pipex = middle_child(pipex, cmd, mini, i);
				i++;
				close(pipex.pipes[i][0]);
				close(pipex.pipes[i][1]);
				cmd = cmd->next;
			}
		}
	}
	wait_for_child(pipex, count);
//	waitpid(pipex.child_id[0], NULL, 0);
//	waitpid(pipex.child_id[1], NULL, 0);
//	waitpid(-1, NULL, 0);
}
