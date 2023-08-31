/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:46:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/31 11:48:38 by bbeltran         ###   ########.fr       */
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

	curr = *redirect;
	while (curr)
	{
		if (curr->type == INPUT)
			input = curr;
		else if (curr->type == OUTPUT || curr->type == APPEND)
			output = curr;
		curr = curr->next;
	}
	if (in_or_out == INPUT && input)
		return (input);
	else if (in_or_out == OUTPUT && output->data)
		return (output);
	return (NULL);
}

/* Iterates through the lexer, if it finds a redirect node type, checks if 
there is a following node and if it is an accessible file. If it has found 
a input redirect it will check for existance and reading permissions, if 
it's a output redirect only for writing permissions*/
int	check_redir_access(t_lexer **lexer)
{
	t_lexer	*curr;
	int		new;

	curr = *lexer;
	new = 0;
	while (curr)
	{
		if (curr->type == REDIR)
		{
			if (redirect_type(curr->data) == 1 && curr->next
				&& access(curr->next->data, F_OK | R_OK) == -1)
			{
				printf("%s: No such file or directory\n", curr->next->data);
				return (0);
			}
			else if (redirect_type(curr->data) == 2 && curr->next)
			{
				if (access(curr->next->data, F_OK) == -1)
				{
					new = open(curr->next->data, O_CREAT, 0644);
					if (new < 0)
					{
						printf("Error creating file or directory\n");
						return (0);
					}
					close(new);
				}
			}
		}
		curr = curr->next;
	}
	return (1);
}
