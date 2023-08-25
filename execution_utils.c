/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:37 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/25 10:32:33 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_executor(t_shell *mini)
{
	t_lexer	*curr;
	int		times;

	curr = *mini->lex;
	times = 0;
	while (curr)
	{
		if (curr->type == BUILTIN)
			times = call_builtins(curr, mini);
		if (times > 0)
		{
			while (times--)
				curr = curr->next;
		}
		else
			curr = curr->next;
	}
}
