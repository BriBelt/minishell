/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/05 17:35:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;
	int		in;
	int		out;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_shell));
	if (!mini)
		return (0);
	if (envp && envp[0])
		mini->envp = copy_envp(envp);
	else
		mini->envp = NULL;
	mini->exit_status = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	minishell_exe(mini, in, out);
	return (0);
}

void	minishell_exe(t_shell *mini, int in, int out)
{
	char	*rd;

	while (1)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
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
