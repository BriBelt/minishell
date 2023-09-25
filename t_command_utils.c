/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:50:49 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/25 14:56:06 by bbeltran         ###   ########.fr       */
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
			|| (ptr->type == STR || ptr->type == BUILTIN || ptr->type == FLAG))
			size++;
		ptr = ptr->next;
	}
	return (size);
}

void	set_redir(t_lexer *ptr, int *redir)
{
	if (ptr->type == REDIR || ptr->type == HERE)
		*redir = 1;
}

t_lexer	*set_args(t_lexer *ptr, char **args, int *i, int *redir)
{
	if ((ptr->type == FIL && !(*redir))
		|| (ptr->type == STR || ptr->type == BUILTIN || ptr->type == FLAG))
	{
		args[*i] = ft_strdup(ptr->data);
		(*i)++;
	}
	ptr = ptr->next;
	return (ptr);
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
		set_redir(ptr, &redir);
		if ((ptr->type == DEL || ptr->type == FIL) && redir && ptr->next)
		{
			ptr = ptr->next;
			if (ptr->type != REDIR && ptr->type != HERE)
				redir = 0;
			if (ptr->type == PIPE)
				break ;
		}
		ptr = set_args(ptr, args, &i, &redir);
	}
	return ((args[i] = NULL), args);
}
