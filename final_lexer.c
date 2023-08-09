/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:41:05 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/09 17:35:30 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*joined_data(t_lexer *curr, size_t *count)
{
	char	*aux;
	char	*final_str;
	char	*joined;
	t_lexer	*ptr;

	final_str = NULL;
	ptr = curr;
	while (ptr)
	{
		if (ptr->join)
		{
			if (joined)
				aux = joined;
			else
				aux = ptr->data;
			joined = ft_strjoin(aux, ptr->next->data);
//			free(aux);
			ptr = ptr->next;
			(*count)++;
		}
		if (!ptr->join)
		{
//			printf("found the node join 0: %s\n", ptr->data);
			final_str = ft_strjoin(joined, ptr->data);
			free(joined);
			break ;
		}
		ptr = ptr->next;
	}
	return (final_str);
}*/

size_t	nodes_to_join(t_lexer *node)
{
	size_t	count;
	t_lexer	*ptr;

	ptr = node;
	count = 0;
	while (ptr)
	{
		if (ptr->join)
			count++;
		if (!ptr->join)
		{
			count++;
			break ;
		}
		ptr = ptr->next;
	}
	return (count);
}

char	*join_nodes(t_lexer *node, size_t count)
{
	size_t	size;
	size_t	i;
	char	*joined;
	t_lexer	*ptr;

	size = 0;
	i = 0;
	ptr = node;
	joined = malloc(sizeof(char) * size);
	while (i++ < count && ptr)
	{
		size += ft_strlen(ptr->data);
		ptr = ptr->next;
	}
	ptr = node;
	i = 0;
	while (i++ < count && ptr)
	{
		joined = ft_strjoin(joined, ptr->data);
		ptr = ptr->next;
	}
	return (joined);
}

t_lexer	**create_final_lex(t_lexer **lst)
{
	t_lexer	**final;
	t_lexer	*curr;
	size_t	c;

	final = malloc(sizeof(t_lexer *));
	if (!final)
		return (NULL);
	*final = NULL;
	curr = *lst;
	while (curr)
	{
		if (curr->join)
		{
			c = nodes_to_join(curr);
			ft_lexer_insert(final, join_nodes(curr, c), curr->index, 1);
			while (c-- && curr)
				curr = curr->next;
		}
		else if (!curr->join)
		{
			printf("no join, %s\n", curr->data);
			ft_lexer_insert(final, ft_strdup(curr->data), curr->index, 0);
		}
		curr = curr->next;
	}
	return (final);
}
/*t_lexer	**create_final_lex(t_lexer **lst)
{
	t_lexer	**final;
	t_lexer	*curr;
	int		loop;

	loop = 0;
	while (curr && curr->join)
	{
		loop = 1;
		j_data = ft_strjoin(curr->data, curr->next->data);
		curr = curr->next;
	}
	while (curr && !curr->join && !loop)
	{
		ft_lexer_insert(final, ft_strdup(curr->data), curr->index, 0);
		curr = curr->next;
	}
	if (loop && curr->next)
		curr = curr->next;
	return (final);
}*/
/*t_lexer	**create_final_lex(t_lexer **lst)
{
	t_lexer	**final;
	t_lexer	*curr;
	char	*new_data;

	curr = *lst;
	new_data = NULL;
	final = malloc(sizeof(t_lexer *));
	if (!final)
		return (NULL);
	while (curr)
	{
		if (curr->join)
		{
			while (curr)
			{
				if (curr->next)
				{
					new_data = ft_strjoin(curr->data, curr->next->data);
					ft_lexer_insert(final, new_data, curr->index, curr->join);
				}
				if (!curr->next->join)
				{
					curr = curr->next;
					break;
				}
			}
			curr = curr->next;
		}
		new_data = curr->data;
		ft_lexer_insert(final, new_data, curr->index, curr->join);
		}
		curr = curr->next;
	}
	return (final);
}*/
