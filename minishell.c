/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/23 11:41:27 by bbeltran         ###   ########.fr       */
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

void	executor(t_shell *mini)
{
	t_lexer	*curr;

	curr = *mini->lex;
	while (curr)
	{
		if (curr->type == BUILTIN)
			call_builtins(curr, mini);
		curr = curr->next;
	}
}
void	minishell_exe(t_shell *mini)
{
	char	*rd;

	while (1)
	{
		rd = readline("minishell>");
		mini->lex = ft_parser(mini, rd);
		if (mini->lex)
			executor(mini);
	}
}
