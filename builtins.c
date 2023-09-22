/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:10:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 16:23:25 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_builtin(t_shell *mini, t_pipex pipex)
{
	int	here_fd;

	here_fd = -1;
	get_file_des(&pipex, (*mini->cmds)->redirect);
	if (mini->curr_heredoc < mini->in_heredocs)
		here_fd = open_heredoc_file(mini);
	if (here_fd != -1)
		(dup2(here_fd, STDIN), close(here_fd));
	else if (pipex.in_fd != -1)
		(dup2(pipex.in_fd, STDIN), close(pipex.in_fd));
	if (pipex.out_fd != -1)
		(dup2(pipex.out_fd, STDOUT), close(pipex.out_fd));
	call_builtins(*mini->cmds, mini);
}

int	builtin_arg(t_command *node)
{
	if (!node->args[0])
		return (0);
	if (!ft_strcmp(node->args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(node->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(node->args[0], "env"))
		return (1);
	else if (!ft_strcmp(node->args[0], "echo"))
		return (1);
	else if (!ft_strcmp(node->args[0], "unset"))
		return (1);
	else if (!ft_strcmp(node->args[0], "export"))
		return (1);
	else if (!ft_strcmp(node->args[0], "exit"))
		return (1);
	return (0);
}

/* This function's purpose is only to call check the given node, if the 
 * node->data of the lexer is the same as any of the specified builtins, it
 * executes the corresponding command for the builtin. */
int	call_builtins(t_command *node, t_shell *mini)
{
	if (!node->args[0])
		return (0);
	if (!ft_strcmp(node->args[0], "pwd"))
		return (ft_pwd(), 1);
	else if (!ft_strcmp(node->args[0], "cd"))
		return (ft_cd(node), 1);
	else if (!ft_strcmp(node->args[0], "env") && mini->envp)
		return (ft_env(node, mini->envp), 1);
	else if (!ft_strcmp(node->args[0], "echo"))
		return (ft_echo(node), 1);
	else if (!ft_strcmp(node->args[0], "unset"))
	{
		if (mini->envp)
			mini->envp = ft_unset(mini->envp, node);
		return (1);
	}
	else if (!ft_strcmp(node->args[0], "export"))
	{
		mini->envp = ft_export(mini->envp, node);
		return (1);
	}
	else if (!ft_strcmp(node->args[0], "exit"))
		ft_exit(mini);
	return (0);
}
