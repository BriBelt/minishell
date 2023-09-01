/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:36:01 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/01 13:01:06 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* Returns the value of REDIR if the *content is the same as a redirection char,
 * if the *content is a pipe, returns PIPE value, else returns a 0. */
int	redirect_or_pipe(char *content)
{
	int	len;

	len = ft_strlen(content);
	if (!ft_strncmp(content, "<<", len)) 
		return (REDIR);
	if (!ft_strncmp(content, ">>", len)) 
		return (REDIR);
	if (!ft_strncmp(content, "<", len)) 
		return (REDIR);
	if (!ft_strncmp(content, ">", len)) 
		return (REDIR);
	if (!ft_strncmp(content, "|", len)) 
		return (PIPE);
	return (0);
}

/* Compares the *content with each builtin name, if they are the same, returns
 * BUILTIN, else returns a STR. */
int	is_builtin(char *content)
{
	int	len;

	len = ft_strlen(content);
	if (!ft_strncmp(str_tolow(content), "echo", len))
		return (BUILTIN);
	if (!ft_strncmp(str_tolow(content), "pwd", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "cd", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "export", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "exit", len))
		return (BUILTIN);
	if (!ft_strncmp(content, "unset", len))
		return (BUILTIN);
	if (!ft_strncmp(str_tolow(content), "env", len))
		return (BUILTIN);
	return (STR);
}

/* Differentiates between a possible COMMAND or a STR by checking for access();
 * of each possible path for *content. */
int	is_command(char *content)
{
	char	*com_path;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths("PATH");
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		com_path = ft_strjoin(tmp, content);
		free(tmp);
		if (!access(com_path, F_OK | X_OK))
			return (free_2D_array(paths), COMMAND);
		free(com_path);
		i++;
	}
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
			curr->type = is_command(curr->data);
			if (curr->type == STR)
				curr->type = flag_or_envar(curr->data);
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
