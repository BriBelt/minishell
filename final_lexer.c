/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:41:05 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/10 12:14:33 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	nodes_to_join(t_lexer **first)
{
	t_lexer	*curr;
	size_t	count;

	curr = *first;
	count = 0;
	while (curr)
	{
		if (curr->join)
			count++;
		curr = curr->next;
	}
	return (count);
}

size_t	new_node_len(t_lexer **first, size_t count)
{
	size_t	len;
	size_t	i;
	t_lexer	*curr;

	curr = *first;
	len = 0;
	i = 0;
	while (curr && i < count)
	{
		if (curr->join)
		{
			len += ft_strlen(curr->data);
			i++;
		}
		curr = curr->next;
	}
	if (count && i == count)
		len += ft_strlen(curr->data);
	return (len);
}

char	*join_nodes(t_lexer **first, size_t count)
{
	char	*joined;
	t_lexer	*curr;
	size_t	size;
	size_t	i;

	size = new_node_len(first, count);
	joined = ft_calloc(size + 1, sizeof(char));
	if (!joined)
		return (NULL);
	curr = *first;
	i = 0;
	while (curr && i < count)
	{
		if (curr->join)
		{
			joined = ft_strjoin(joined, curr->data);
			i++;
		}
		curr = curr->next;
	}
	if (count && i == count)
		joined = ft_strjoin(joined, curr->data);
	return (joined);
}

/*t_lexer	**create_final_lex(t_lexer **first)
{
	t_lexer	**final;
	t_lexer	*curr;
	size_t	count;

	final = malloc(sizeof(t_lexer *));
	if (!final)
		return (NULL);
	*final = NULL;
	curr = *first;
	count = nodes_to_join(first);
	while (curr)
	{
		if (curr->join)
		{

	}
	
}*/
