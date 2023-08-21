/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:58:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 11:09:52 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_lexer *node, t_shell *mini)
{
	if (node->next)
	{
		if (node->next->type == VAR)
			node->next->data = expand_envar(node->next->data, mini);
		printf("%s\n", node->next->data);
	}
}
