/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:07:01 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/17 17:21:00 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

void	clean_false_join(t_lexer **lex)
{
	t_lexer	*curr;

	curr = *lex;
	while (curr)
	{
		if (curr->join == 1)
		{
			if (!ft_strchr(curr->data, '\"') && !ft_strchr(curr->data, '\''))
				curr->join = 0;
		}
		curr = curr->next;
	}
}

void	set_new_join(t_lexer **first, char *rd)
{
	t_lexer *curr;
	int		i;
	int		j;
	int		space;
	int		quoted;

	i = 0;
	curr = *first;
	while (curr)
	{
		quoted = 0;
		if (ft_strchr(curr->data, '\'') || ft_strchr(curr->data, '\"'))
		{
			printf("Found quote at node: %s\n", curr->data);
			quoted = 1;
		}
		j = 0;
		while (rd[i] && curr->data[j])
			(i++, j++);
		if (rd[i] == ' ')
		{
			printf("Found space at node: %s, i: %i\n", curr->data, i);
			space = 1;
		}
		if (quoted && !space)
		{
			if (!curr->join)
			{
				curr->join = 1;
				printf("curr->join: %zu\n", curr->join);
			}
			if (curr->next)
			{
				curr = curr->next;
				if (ft_strchr(curr->data, '\'') || ft_strchr(curr->data, '\"'))
				{
					printf("Found quote at node: %s\n", curr->data);
					quoted = 1;
				}
				if (quoted)
					curr->join = 1;
				printf("next->join: %zu\n", curr->join);
			}
			printf("New join! %s, join: %zu\n", curr->data, curr->join);
		}
		if (space)
		{
			curr->join = 0;
			space = 0;
			printf("There's a space at %s\n", curr->data);
		}
		curr = curr->next;
	}
}

/*void	clean_false_join(t_lexer **first, char *rd)
{
	t_lexer	*curr;
	int		i;
	int		j;
	int		space;

	i = 0;
	space = 0;
	curr = *first;
	while (curr)
	{
		j = 0;
		while (rd[i] && curr->data[j])
		{
			i++;
			j++;
		}
		if (rd[i] == ' ' && curr->next)
			space = i;


		
		curr = curr->next;
	}
}*/

/*void	clean_false_join(t_lexer **first, char *rd)
{
	t_lexer *curr;
	int		i;
	int		j;

	i = 0;
	curr = *first;
	while (curr)
	{
		j = 0;
		while (rd[i])
		{
			if (rd[i] == ' ' && curr->data[j] == '\0')
			{
				if (curr->next && !ft_strchr(curr->next->data)
					curr->next->join = 0;
				else
					node->next->join = 1;
				break ;
			}
			i++;
			j++;
		}
		curr = curr->next;
	}
}*/
