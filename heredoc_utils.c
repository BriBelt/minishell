/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:34:43 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 18:55:53 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function returns a pointer to the last node in the **lexer that its 
 * node->data is a heredoc (<<). */
t_lexer	*check_for_heredoc(t_lexer **lexer)
{
	t_lexer	*curr;
	t_lexer	*here_doc;

	curr = *lexer;
	here_doc = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->data, "<<"))
			here_doc = curr;
		curr = curr->next;
	}
	return (here_doc);
}

/* Receives the **lexer, and calls the check_for_heredoc(); function, and
 * checks if the next node exists and sets it as a delimiter. */
char	*find_delimiter(t_lexer **lexer)
{
	t_lexer	*here_doc;
	char	*del;

	here_doc = check_for_heredoc(lexer);
	if (!here_doc->next)
		return (perror("Syntax Error"), NULL);
	del = here_doc->next->data;
	return (del);
}

/* This function returns the number*/
int	heredoc_or_input(t_red **redirects)
{
	t_red	*curr;
	int		type;
	int		heredoc_count;

	curr = *redirects;
	type = 0;
	heredoc_count = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			type = curr->type;
			heredoc_count++;
		}
		if (curr->type == INPUT)
			type = curr->type;
		curr = curr->next;
	}
	if (type == HEREDOC)
		return (heredoc_count);
	return (0);
}

int	open_heredoc_file(t_shell *mini)
{
	int		heredoc_num;
	char	*name;
	char	*num;
	int		fd;

	heredoc_num = mini->curr_heredoc;
	num = ft_itoa(heredoc_num);
	fd = 0;
	if (heredoc_num > -1)
	{
		name = ft_strjoin("/tmp/.heredoc_", num);
		fd = open(name, O_RDWR, 0644);
		(free(name), free(num));
	}
	return (fd);
}

int	here_counter(t_command **commands)
{
	t_command	*curr;
	t_red		*red_curr;
	int			size;

	curr = *commands;
	size = 0;
	while (curr)
	{
		red_curr = *curr->redirect;
		while (red_curr)
		{
			if (red_curr->type == HEREDOC)
				size++;
			red_curr = red_curr->next;
		}
		curr = curr->next;
	}
	return (size);
}
