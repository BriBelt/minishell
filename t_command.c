/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:29:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 13:30:04 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_size(t_lexer *curr)
{
	t_lexer	*ptr;
	int		size;

	ptr = curr;
	size = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type != REDIR)
			size++;
		if (ptr->type == REDIR)
			ptr += 2;
		else
			ptr = ptr->next;
	}
	return (size);
}

char	**get_args(t_lexer *curr)
{
	char	**args;
	t_lexer	*ptr;
	int		i;

	ptr = curr;
	i = 0;
	args = ft_calloc(args_size(curr) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type != REDIR)
		{
			args[i] = ft_strdup(ptr->data);
			i++;
		}
		if (ptr->type == REDIR)
			ptr += 2;
		else
			ptr = ptr->next;
	}
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
