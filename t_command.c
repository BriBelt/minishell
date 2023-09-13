/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:29:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/12 12:55:26 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterates though the **lexer from the given *node, checks the amount of
 **/
int	args_size(t_lexer *curr)
{
	t_lexer	*ptr;
	int		size;
	int		redir;

	ptr = curr;
	size = 0;
	redir = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == REDIR || ptr->type == HERE)
			redir = 1;
		if ((ptr->type == FIL || ptr->type == DEL) && redir && ptr->next)
		{
			ptr = ptr->next;
			if (ptr->type != REDIR && ptr->type != HERE)
				redir = 0;
			if (ptr->type == PIPE)
				break ;
		}
		if ((ptr->type == FIL && !redir)
		   || (ptr->type == STR || ptr->type == BUILTIN))
			size++;
		ptr = ptr->next;
	}
	return (size);
}

char	**get_args(t_lexer *curr)
{
	char	**args;
	t_lexer	*ptr;
	int		i;
	int		redir;

	ptr = curr;
	i = 0;
	redir = 0;
	args = ft_calloc(args_size(curr) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == REDIR || ptr->type == HERE)
			redir = 1;
		if ((ptr->type == DEL || ptr->type == FIL) && redir && ptr->next)
		{
			ptr = ptr->next;
			if (ptr->type != REDIR && ptr->type != HERE)
				redir = 0;
			if (ptr->type == PIPE)
				break ;
		}
		if ((ptr->type == FIL && !redir)
			|| (ptr->type == STR || ptr->type == BUILTIN))
		{
			args[i] = ft_strdup(ptr->data);
			i++;
		}
		ptr = ptr->next;
	}
	args[i] = NULL;
	return (args);
}

t_command	*ft_cmd_new(t_lexer *curr, t_red **redirects)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = get_args(curr);
	node->redirect = redirects;
	node->next = NULL;
	return (node);
}

void	ft_cmd_insert(t_command **lst, t_lexer *node, t_red **redirects)
{
	t_command	*new;
	t_command	*ptr;

	new = ft_cmd_new(node, redirects);
	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_command	**create_command_list(t_lexer **lexer)
{
	t_red		**red;
	t_command	**commands;
	t_lexer		*curr;

	curr = *lexer;
	commands = malloc(sizeof(t_command *));
	if (!commands)
		return (NULL);
	*commands = NULL;
	while (curr)
	{
		if (curr && (curr->type == PIPE || curr->index == 0))
		{
			if (curr->type == PIPE)
				curr = curr->next;
			red = create_redir_list(curr);
			ft_cmd_insert(commands, curr, red);
		}
		curr = curr->next;
	}
	return (commands);
}
