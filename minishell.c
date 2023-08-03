/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/03 17:48:59 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("Leaks a.out");
}

int	main(int argc, char **argv, char **envp)
{
	atexit(ft_leaks);
	(void)argc;
	(void)argv;
	t_shell *mini;

	mini = malloc(sizeof(t_shell));
	if (!mini)
		/*should return an error, create a new exit function for errors*/
		return (0);
	mini->envp = copy_envp(envp);
	minishell_exe(mini);
	/* Check if the new envp is not empty, if it is then the program was
	 * launched with env -i */
	return (0);
}

void	minishell_exe(t_shell *mini)
{
	char	*rd;
	char	*new_rd;
	char	**words;
	int		i = 0;

	while (1)
	{
		if (mini->lex)
			free_list(mini->lex);
		rd = readline("minishell>");
		new_rd = handle_quotes(rd);
		printf("new_rd: %s\n", new_rd);
		words = ft_split(new_rd, '!');
		/* Should also be separated by quotes after assigning type value
		 * to each node. */
		mini->lex = create_list(words);
		def_type(mini->lex);
		clean_quotes(mini->lex);
//		curr = *mini->lex;
		i = 0;
		while (i < 3)
		{
			printf("index: %i, node: %s, type: %i\n", (*mini->lex)->index, (*mini->lex)->data, (*mini->lex)->type);
			*mini->lex = (*mini->lex)->next;
			i++;
		}
	}
}
