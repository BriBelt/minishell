/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:58:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/20 14:56:01 by bbeltran         ###   ########.fr       */
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

int	check_for_flag(char	**args)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '-' && only_n(args[i]))
			count++;
	}
	return (count);
}

void	echo_flagged(t_command *curr)
{
	int	i;

	i = check_for_flag(curr->args);
	while (curr->args[i])
	{
		if (!curr->args[i + 1])
			printf("%s", curr->args[i]);
		else
			printf("%s ", curr->args[i]);
		i++;
	}
}

void	echo_no_flag(t_command *curr)
{
	int	i;

	i = 0;
	while (curr->args[++i])
		printf("%s ", curr->args[i]);
	printf("\n");
}

void	ft_echo(t_command *node)
{
	t_command	*curr;

	curr = node;
	if (curr)
	{
		if (check_for_flag(curr->args) > 1)
			echo_flagged(curr);
		else
			echo_no_flag(curr);
	}
	g_global.exit_stat = 0;
}
