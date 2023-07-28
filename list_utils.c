/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:23:21 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 16:28:10 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_lexernew(char *content, int i)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (0);
	node->data = content; 
	node->next = NULL; 
	node->index = i; 
	return (node);
}

void	ft_lexer_insert(t_lexer	**lst, char *content, int i)
{
	t_lexer	*node;
	t_lexer	*ptr;

	node = ft_lexernew(content, i);
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

t_lexer	**create_list(char **words)
{
	int		i;
	t_lexer	**lst;

	i = 0;
	lst = malloc(sizeof(t_lexer *));
	*lst = NULL;
	while (words[i])
	{
		ft_lexer_insert(lst, words[i], i);
		i++;
	}
	return (lst);
}
