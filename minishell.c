/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 19:20:19 by bbeltran         ###   ########.fr       */
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
		mini->envp = ft_calloc(1, sizeof(char *));
	if (!mini->envp)
		return (0);
	g_global.exit_stat = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	g_global.pwd = getcwd(NULL, 0);
	minishell_exe(mini, in, out);
	return (g_global.exit_stat);
}

char	*ft_readline(char *aux)
{
	char	*rd;

	aux = readline("minishell> ");
	if (!aux)
		ft_exit(NULL);
	rd = ft_strtrim(aux, " \t\n\r\v\f");
	free(aux);
	return (rd);
}

void	minishell_exe(t_shell *mini, int in, int out)
{
	char	*rd;
	char	*aux;

	aux = NULL;
	(signal(SIGINT, signal_handler), signal(SIGQUIT, SIG_IGN));
	while (1)
	{
		(dup2(in, STDIN_FILENO), dup2(out, STDOUT_FILENO));
		rd = ft_readline(aux);
		if (rd && ft_strlen(rd) > 0)
		{
			add_history(rd);
			mini->lex = ft_parser(mini, rd);
			if (mini->lex)
			{
				mini->cmds = create_command_list(mini->lex);
				executor(mini);
				(free_t_command(mini->cmds), free_t_lexer(mini->lex));
			}
		}
		else
			free(rd);
	}
}
