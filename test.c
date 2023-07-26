/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:45:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/26 13:51:49 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	minishell_exe();
	return (0);
}

void	minishell_exe(void)
{
	char	*rd;
	
	while (1)
	{
		rd = readline("minishell> ");
		printf("%s", rd);
		if (rd[0] != '\0')
			printf("\n");
		add_history(rd);
		free(rd);
	}
}
