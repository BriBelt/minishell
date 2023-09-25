/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:35:10 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 17:34:16 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	found_del(t_here *h)
{
	if (h->rd && !ft_strcmp(h->rd, h->dels[h->i]))
	{
		if (h->created)
		{
			h->created = 0;
			close(h->fd);
		}
		h->i++;
		if (!h->dels[h->i])
			return (0);
	}
	if (h->rd && h->fd > 0 && h->i == h->in_h[h->j - 1] - 1)
		(write(h->fd, h->rd, ft_strlen(h->rd)), write(h->fd, "\n", 1));
	if (!h->rd && !h->dels[h->i + 1])
		return (0);
	if (!h->rd)
		h->i++;
	free(h->rd);
	return (1);
}

int	create_tmp_file(t_here *h, t_command **commands)
{
	while (++h->j < count_input_heredocs(commands))
	{
		if (h->i == h->in_h[h->j] - 1 && !h->created)
		{
			h->num = ft_itoa(h->j);
			h->name = ft_strjoin("/tmp/.heredoc_", h->num);
			h->fd = open(h->name, O_CREAT | O_RDWR, 0644);
			(free(h->num), free(h->name));
			if (h->fd < 0)
				return (0);
			h->created = 1;
			h->j++;
			break ;
		}
	}
	return (1);
}

int	here_doc_exe(t_command **commands)
{
	t_here	h;

	h.child = fork();
	if (!h.child)
	{
		signal(SIGINT, SIG_DFL);
		h.i = 0;
		h.created = 0;
		h.dels = find_all_del(commands);
		h.in_h = input_heredocs(commands);
		while (1)
		{
			h.rd = readline("> ");
			h.j = -1;
			if (!create_tmp_file(&h, commands))
				return (perror("Error creating the temp file"), -1);
			if (!found_del(&h))
				exit(0);
		}
	}
	return (ft_heredoc_signal(h.child));
}
