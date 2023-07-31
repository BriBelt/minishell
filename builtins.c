/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:10:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/31 18:52:06 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtins(t_lexer *node, char **envp)
{
	int		len;

	len = ft_strlen(node->data);
	if (!ft_strcmp(node->data, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(node->data, "cd"))
		ft_cd(node);
	else if (!ft_strcmp(node->data, "env"))
		ft_env(envp);
}
