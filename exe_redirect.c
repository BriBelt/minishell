/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:46:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 12:13:22 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks the type of redirect found in node->data(input,1 or output,2). 
Usefull for checking wich is the last redirect(before pipe or NULL).*/
/*int	redirect_type(char *data)
{
	if (!ft_strcmp(data, "<"))
		return (1);
	if (!ft_strcmp(data, ">") || !ft_strcmp(data, ">>"))
		return (2);
	return (0);
}*/

/* By introducing as an argument the type of redirect and the starting node, 
it will search for the last position of that redirect in the lexer before NULL 
or pipe. Usefull since it will be the only one that passes the input or output 
to a command or pipe.*/
/*int	redirect_last_position(t_lexer *start, int type)
{
	t_lexer	*curr;
	int		input_last;
	int		output_last;

	input_last = 0;
	output_last = 0;
	curr = start;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIR)
		{
			if (redirect_type(curr->data) == 1)
				input_last = curr->index;
			else if (redirect_type(curr->data) == 2)
				output_last = curr->index;
		}
		curr = curr->next;
	}
	if (type == 1)
		return (input_last);
	else if (type == 2)
		return (output_last);
	return (0);
}*/

/* Iterates through the lexer, if it finds a redirect node type, checks if 
there is a following node and if it is an accessible file. If it has found 
a input redirect it will check for existance and reading permissions, if 
it's a output redirect only for writing permissions*/
/*int	check_redir_access(t_lexer **lexer)
{
	t_lexer	*curr;

	curr = *lexer;
	while (curr)
	{
		if (curr->type == REDIR)
		{
			if (redirect_type(curr->data) == 1 && curr->next
				&& access(curr->next->data, F_OK | R_OK))
			{
				printf("%s: No such file or directory\n", curr->next->data);
				return (0);
			}
			else if (redirect_type(curr->data) == 2 && curr->next
				&& access(curr->next->data, W_OK))
			{
				printf("%s: No such file or directory\n", curr->next->data);
				return (0);
			}
		}
		curr = curr->next;
	}
	return (1);
}*/
