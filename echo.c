/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:58:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 12:24:09 by bbeltran         ###   ########.fr       */
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

void	echo_flagged(t_lexer *curr, int *times)
{
	curr = curr->next;
	(*times)++;
	while (curr && curr->type != PIPE && curr->type != REDIR)
	{
		printf("%s", curr->data);
		curr = curr->next;
		(*times)++;
	}
}

void	echo_no_flag(t_lexer *curr, int *times)
{
	while (curr && curr->type != PIPE && curr->type != REDIR)
	{
		printf("%s ", curr->data);
		curr = curr->next;
		(*times)++;
	}
	printf("\n");
}

int	ft_echo(t_lexer *node)
{
	t_lexer	*curr;
	int		times;

	curr = node->next;
	times = 0;
	if (curr)
	{
		if (curr->type == FLAG && only_n(curr->data))
			echo_flagged(curr, &times);
		else
			echo_no_flag(curr, &times);
	}
	return (times);
}
