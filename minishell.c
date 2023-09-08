/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:04:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/08 16:03:47 by bbeltran         ###   ########.fr       */
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
	global.exit_stat = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	global.pwd = getcwd(NULL, 0);
	minishell_exe(mini, in, out);
	return (global.exit_stat);
}

void	minishell_exe(t_shell *mini, int in, int out)
{
	char	*rd;
	char	*aux;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		aux = readline("minishell>");
		if (!aux)
			ft_exit(NULL);
		rd = ft_strtrim(aux, " \t\n\r\v\f");
		free(aux);
		if (rd && ft_strlen(rd) > 0)
		{
			add_history(rd);
			mini->lex = ft_parser(mini, rd);
			if (mini->lex)
			{
				mini->cmds = create_command_list(mini->lex);
				t_command *curr = *mini->cmds;
				int i = 0;
				while (curr)
				{
					while (curr->args[i])
					{
						printf("Command[%i]: %s\n", i, curr->args[i]);
						i++;
					} 
					curr = curr->next;
				}
				executor(mini);
			}
			else
				free(rd);
		}
	}
}
