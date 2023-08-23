/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:10:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 11:30:52 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function's purpose is only to call check the given node, if the 
 * node->data of the lexer is the same as any of the specified builtins, it
 * executes the corresponding command for the builtin. */
void	call_builtins(t_lexer *node, t_shell *mini)
{
	if (!ft_strcmp(node->data, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(node->data, "cd"))
		ft_cd(node);
	else if (!ft_strcmp(node->data, "env"))
		ft_env(mini->envp);
	else if (!ft_strcmp(node->data, "echo"))
		ft_echo(node);
	else if (!ft_strcmp(node->data, "unset"))
		mini->envp = ft_unset(mini->envp, node);
	else if (!ft_strcmp(node->data, "export"))
		mini->envp = ft_export(mini->envp, node);
}
