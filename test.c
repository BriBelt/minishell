/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:45:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/21 11:27:42 by jaimmart         ###   ########.fr       */
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
	char	**words;
	t_lexer	**lst;
	t_lexer	*ptr;

	while (1)
	{
		rd = readline("minishell>");
		words = ft_split(rd, ' ');
		lst = create_list(words);
		def_type(lst);
		ptr = *lst;
		while (ptr)
		{
			if (ptr->type == BUILTIN)
				call_builtins(ptr, mini->envp, mini);
			ptr = ptr->next;
		}
		if (rd[0] != '\0')
			printf("\n");
		add_history(rd);
		rl_on_new_line();
		if (!ft_strncmp(rd, "exit", ft_strlen(rd)))
		{
			free(rd);
			free_2D_array(mini->envp);
			free(mini);
			clear_history();
			free_list(lst);
			exit(0);
		}
	}
}
