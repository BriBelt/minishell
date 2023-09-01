/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:35:10 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/01 14:22:01 by bbeltran         ###   ########.fr       */
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

/* This function is only called when a here_doc symbol (<<) is found.
 * First, deletes the temporal file (.hd_file) if it already exists. After
 * that creates a new .hd_file and checks for errors occurred during the
 * opening of the file. Finally, replicates the here doc behavior in bash,
 * saving the *here_line into the .hd_file. */
void	here_doc_exe(char *del)
{
	char	*here_line;
	int		temp_file;

	unlink("/tmp/.hd_file");
	temp_file = open("/tmp/.hd_file", O_CREAT | O_APPEND | O_RDWR, 777);
	if (temp_file < 0)
	{
		perror("Error creating the temp file");
		return ;
	}
	while (1)
	{
		here_line = readline(">");
		if (!ft_strcmp(here_line, del))
			break ;
		write(temp_file, here_line, ft_strlen(here_line));
		write(temp_file, "\n", 1);
		free(here_line);
	}
	close(temp_file);
}
