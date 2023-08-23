/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:58:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 11:38:14 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_n(char	*data)
{
	int	i;

	i = 0;
	while (data[++i])
	{
		if (data[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_lexer *node)
{
	t_lexer	*curr;

	curr = node->next;
	if (curr)
	{
		if (curr->type == FLAG && only_n(curr->data))
		{
			curr = curr->next;
			while (curr)
			{
				printf("%s", curr->data);
				curr = curr->next;
			}
		}
		else
		{
			while (curr)
			{
				printf("%s ", curr->data);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}
