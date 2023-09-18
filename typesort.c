/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:36:01 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/18 12:07:24 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the value of REDIR if the *content is the same as a redirection char,
 * if the *content is a pipe, returns PIPE value, else returns a 0. */
int	redirect_or_pipe(char *content)
{
	if (!ft_strcmp(content, "<<"))
		return (HERE);
	if (!ft_strcmp(content, ">>"))
		return (REDIR);
	if (!ft_strcmp(content, "<"))
		return (REDIR);
	if (!ft_strcmp(content, ">"))
		return (REDIR);
	if (!ft_strcmp(content, "|"))
		return (PIPE);
	return (0);
}

/* Compares the *content with each builtin name, if they are the same, returns
 * BUILTIN, else returns a STR. */
int	is_builtin(char *content)
{
	int	len;

	len = ft_strlen(content);
	if (!ft_strncmp(content, "echo", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "pwd", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "cd", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "export", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "exit", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "unset", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "env", len))
		return (BUILTIN);
	return (STR);
}

/* Just like what_type();, changes the lexer->type(STR) value by calling the
 * is_command();, flag_or_envar(); or is_file(); */
void	str_type(t_lexer **lst)
{
	t_lexer	*curr;

	curr = *lst;
	while (curr)
	{
		if (curr->type == STR)
		{
			curr->type = flag_or_envar(curr->data, curr->join);
			if (curr->type == STR)
				curr->type = is_file(curr->data);
		}
		curr = curr->next;
	}
}

/* Sets the value of lexer->type depending on the previously defined types
 * (minishell.h) by calling the redirect_or_pipe(); or the str_type(); */
void	def_type(t_lexer **lst)
{
	t_lexer	*curr;

	curr = *lst;
	while (curr)
	{
		if (redirect_or_pipe(curr->data) && curr->join == 0)
			curr->type = redirect_or_pipe(curr->data);
		else
			curr->type = is_builtin(curr->data);
		curr = curr->next;
	}
	is_file_type(lst);
	str_type(lst);
}
