/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:46:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/26 13:44:33 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* By introducing as an argument the type of redirect and the starting node, 
it will search for the last position of that redirect in the lexer before NULL 
or pipe. Usefull since it will be the only one that passes the input or output 
to a command or pipe.*/
t_red	*last_redirect(t_red **redirect, int in_or_out)
{
	t_red	*curr;
	t_red	*input;
	t_red	*output;

	curr = *redirec;
	while (curr)
	{
		if (curr->type == INPUT)
			input = curr;
		else if (curr->type == OUTPUT || curr->type == APPEND)
			output = curr;
		curr = curr->next;
	}
	if (in_or_out == INPUT)
		return (input);
	else if (in_or_out == OUTPUT)
		return (output);
	return (NULL);
}

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
