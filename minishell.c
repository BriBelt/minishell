/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/25 10:31:12 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("Leaks minishell");
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
	t_command	**lst;

	while (1)
	{
		rd = readline("minishell>");
		add_history(rd);
		mini->lex = ft_parser(mini, rd);
		lst = create_command_list(mini->lex);
		t_command	*curr;
		curr = *lst;
		int	i = 0;
		while (curr)
		{
			printf("--new node--\n");
			i = 0;
			while (curr->args[i])
			{
				printf("arg[%i] = %s\n", i, curr->args[i]);
				i++;
			}
			curr = curr->next;
		}
		
		if (mini->lex)
			builtin_executor(mini);
	}
}
