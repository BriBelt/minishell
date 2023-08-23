/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:51:02 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 16:59:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function for the BUILTIN pwd, which, using getcwd(); gives you the current
 * working directory and prints it on the terminal(shell). */
void	ft_pwd(t_lexer *node, int *times)
{
	char	*dir;
	t_lexer	*curr;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	free(dir);
	if (node->next)
	{
		curr = node->next;
		while (curr && curr->type != PIPE && curr->type != REDIR)
		{
			curr = curr->next;
			(*times)++;
		}
	}
}
