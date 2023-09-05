/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/05 11:23:33 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_shell));
	if (!mini)
		(ft_putstr_fd(MEM_ERR, 2) , exit(errno));
	if (!envp[0])
		(ft_putstr_fd("Error: No environment variables\n", 2) , exit(errno));
	mini->envp = copy_envp(envp);
	mini->exit_status = 0;
	minishell_exe(mini);
	/* Check if the new envp isnot empty, if it is then the program was
	 * launched with env -i */
	return (0);
}

void	minishell_exe(t_shell *mini)
{
	char	*rd;

	while (1)
	{
		rd = readline("minishell>");
		if (!rd)
			ft_exit(NULL);
		if (rd && ft_strlen(rd) > 0)
		{
			add_history(rd);
			mini->lex = ft_parser(mini, rd);
			mini->cmds = create_command_list(mini->lex);
			executor(mini);
		}
	}
}
