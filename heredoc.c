/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:35:10 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/12 11:15:05 by jaimmart         ###   ########.fr       */
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

int	open_heredoc_file(t_red **redirects)
{
	int		heredoc_num;
	char	*name;
	int		fd;

	heredoc_num = heredoc_or_input(redirects) - 1;
	printf("heredoc_num = %i\n", heredoc_num);
	fd = 0;
	if (heredoc_num > -1)
	{
		name = ft_strjoin("/tmp/.heredoc_", ft_itoa(heredoc_num));
		printf("--h_file name = %s\n", name);
		fd = open(name, O_APPEND | O_RDWR, 0644);
		printf("open_heredoc_file fd = %i", fd);
		if (fd < 0)
		{
			perror("Error opening the temp file");
			return (0);
		}
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
	int 		*in_here;
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

void	here_doc_exe(t_command **commands)
{
	char		**dels;
	char		*rd;
	char		*tmp_name;
	int			i;
	int			created;
	int			*input_here;
	int			j;
	int			tmp_file;

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
			printf("j = %i\n", j);
			if (i == input_here[j] - 1 && !created)
			{
				tmp_name = ft_strjoin("/tmp/.heredoc_", ft_itoa(j));
				printf("tmp_name = %s\n", tmp_name);
				printf("Before creating file = %s\n", tmp_name);
				tmp_file = open(tmp_name, O_CREAT | O_RDWR, 0644);
				printf("tmp_fd %i\n", tmp_file);
				if (tmp_file < 0)
				{
					perror("Error creating the temp file");
					return ;
				}
				created = 1;
				j++;
				break ;
			}
		}
		printf("j=%i\n", j);
		printf("dels[%i]=%s\n", i, dels[i]);
		if (!ft_strcmp(rd, dels[i]))
		{
			if (i == input_here[j - 1] - 1)
			{
				printf("closed\n");
				created = 0;
				close(tmp_file);
			}
			i++;
			printf("dels[%i] = %s\n", i, dels[i]);
			if (!dels[i])
				break ;
		}
		if (tmp_file > 0 && i == input_here[j - 1] - 1)
			(write(tmp_file, rd, ft_strlen(rd)), write(tmp_file, "\n", 1));
	}
}
