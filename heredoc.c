/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:35:10 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 16:33:24 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_all_del(t_command **commands)
{
	t_command	*curr;
	t_red		*red_curr;
	char		**dels;
	int			i;

	dels = ft_calloc(here_counter(commands) + 1, sizeof(char *));
	if (!dels)
		return (NULL);
	curr = *commands;
	i = 0;
	while (curr)
	{
		red_curr = *curr->redirect;
		while (red_curr)
		{
			if (red_curr->type == HEREDOC)
			{
				dels[i] = ft_strdup(red_curr->data);
				i++;
			}
			red_curr = red_curr->next;
		}
		curr = curr->next;
	}
	return (dels);
}

int	count_input_heredocs(t_command **commands)
{
	t_command	*curr;
	int			count;

	curr = *commands;
	count = 0;
	while (curr)
	{
		if (heredoc_or_input(curr->redirect))
			count++;
		curr = curr->next;
	}
	return (count);
}

int	*input_heredocs(t_command **commands)
{
	int			*in_here;
	t_command	*curr;
	int			pos;
	int			count;
	int			i;

	count = count_input_heredocs(commands);
	in_here = malloc(sizeof(int *) * count);
	if (!in_here)
		return (0);
	curr = *commands;
	pos = 0;
	i = 0;
	while (curr)
	{
		if (heredoc_or_input(curr->redirect))
		{
			pos += heredoc_or_input(curr->redirect);
			in_here[i] = pos;
			i++;
		}
		curr = curr->next;
	}
	return (in_here);
}

int	here_doc_exe(t_command **commands)
{
	char		**dels;
	char		*rd;
	char		*tmp_name;
	int			i;
	int			created;
	int			*input_here;
	int			j;
	int			tmp_file;
	int			here_child;
	char		*num;

	here_child = fork();
	if (!here_child)
	{
		signal(SIGINT, SIG_DFL);
		i = 0;
		created = 0;
		dels = find_all_del(commands);
		input_here = input_heredocs(commands);
		while (1)
		{
			rd = readline("> ");
			j = -1;
			while (++j < count_input_heredocs(commands))
			{
				if (i == input_here[j] - 1 && !created)
				{
					num = ft_itoa(j);
					tmp_name = ft_strjoin("/tmp/.heredoc_", num);
					tmp_file = open(tmp_name, O_CREAT | O_RDWR, 0644);
					(free(num), free(tmp_name));
					if (tmp_file < 0)
						return (perror("Error creating the temp file"), -1);
					created = 1;
					j++;
					break ;
				}
			}
			if (rd && !ft_strcmp(rd, dels[i]))
			{
				if (created)
				{
					created = 0;
					close(tmp_file);
				}
				i++;
				if (!dels[i])
					exit(0);
			}
			if (rd && tmp_file > 0 && i == input_here[j - 1] - 1)
				(write(tmp_file, rd, ft_strlen(rd)), write(tmp_file, "\n", 1));
			if (!rd && !dels[i + 1])
				exit(0);
			if (!rd)
				i++;
			free(rd);
		}
	}
	return (ft_heredoc_signal(here_child));
}
