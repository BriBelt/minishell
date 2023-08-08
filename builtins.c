/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:10:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/05 11:32:51 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function's purpose is only to call check the given node, if the 
 * node->data of the lexer is the same as any of the specified builtins, it
 * executes the corresponding command for the builtin. */
void	call_builtins(t_lexer *node, char **envp, t_shell *mini)
{
	int		len;

	len = ft_strlen(node->data);
	if (!ft_strcmp(node->data, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(node->data, "cd"))
		ft_cd(node);
	else if (!ft_strcmp(node->data, "env"))
		ft_env(envp);
	else if (!ft_strcmp(node->data, "echo"))
		ft_echo(node, mini);
	else if (!ft_strcmp(node->data, "unset"))
		mini->envp = ft_unset(envp, node);
	else if (!ft_strcmp(node->data, "export"))
		mini->envp = ft_export(envp, node);
}
