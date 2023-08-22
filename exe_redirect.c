/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:46:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/22 16:42:54 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_type(char *data)
{
	if (!ft_strcmp(data, "<"))
		return (1);
	if (!ft_strcmp(data, ">") || !ft_strcmp(data, ">>"))
		return (2);
	return (0);
}

int	redirect_last_position(t_lexer *start, int type)
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
}

int	check_redir_access(t_lexer **lexer)
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
}
