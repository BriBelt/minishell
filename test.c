/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:45:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/27 17:49:10 by bbeltran         ###   ########.fr       */
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
	char	**words;
	t_lexer	**lst;
	t_lexer	*ptr;

	while (1)
	{
		rd = readline("minishell>");
		words = ft_split(rd, ' ');
		lst = create_list(words);
		ptr = *lst;
		while (ptr)
		{
			printf("%s, index: %i\n", ptr->str, ptr->index);
			ptr = ptr->next;
		}
		if (rd[0] != '\0')
			printf("\n");
		add_history(rd);
		free(rd);
//		rl_redisplay(); /* idk what this is for*/
		rl_on_new_line();
	}
}
