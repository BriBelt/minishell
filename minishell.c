/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/30 14:44:15 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
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

	while (1)
	{
		rd = readline("minishell>");
		if (ft_strlen(rd) > 0)
		{
			add_history(rd);
			mini->lex = ft_parser(mini, rd);
			mini->cmds = create_command_list(mini->lex);
			executor(mini);
		}
	}
}
