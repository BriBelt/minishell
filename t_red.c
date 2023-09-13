/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_red.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:36:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/13 11:27:22 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_type(char *data)
{
	if (!ft_strcmp(data, "<"))
		return (INPUT);
	if (!ft_strcmp(data, ">"))
		return (OUTPUT);
	if (!ft_strcmp(data, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(data, ">>"))
		return (APPEND);
	return (NO_REDIR);
}

t_red	*ft_red_new(int type, char *content)
{
	t_red	*node;

	node = malloc(sizeof(t_red));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = content;
	node->next = NULL;
	return (node);
}

void	ft_red_insert(t_red **lst, int type, char *content)
{
	t_red	*node;
	t_red	*ptr;

	node = ft_red_new(type, content);
	if (*lst == NULL)
		*lst = node;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}

t_red	**create_redir_list(t_lexer	*curr)
{
	t_red	**red;

	red = malloc(sizeof(t_red *));
	if (!red)
		return (NULL);
	*red = NULL;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIR || curr->type == HERE)
			ft_red_insert(red, redirect_type(curr->data), curr->next->data);
		curr = curr->next;
	}
	return (red);
}
