/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:01:41 by jaimmart32        #+#    #+#             */
/*   Updated: 2023/09/01 13:42:17 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sel_sort_strings(char **strings, int num_strings)
{
	int	i;
	int	j;
	int	min_index;

	i = 0;
	while (i < num_strings - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < num_strings)
		{
			if (strings[j][0] < strings[min_index][0])
				min_index = j;
			j++;
		}
		if (min_index != i)
			swap_strings(&strings[i], &strings[min_index]);
		i++;
	}
}

void	print_sort_env(char **envp)
{
	int	num_strings;
	int	i;

	i = 0;
	num_strings = 0;
	while (envp[num_strings])
		num_strings++;
	sel_sort_strings(envp, num_strings);
	while (i < num_strings)
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}
