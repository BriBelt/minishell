/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:10:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/21 15:14:19 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_tolow(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
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
