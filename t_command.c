/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:29:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 15:53:06 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
