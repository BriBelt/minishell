/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:01:20 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 16:11:45 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# define PIPE_ERR "Syntax error near unexpected token \'|\'\n"
# define REDIR_ERR "Syntax error near unexpected redirect token\n"
# define QUOTE_ERR "Syntax error: Unclosed quotes\n"

/* Enum for classifying the type of redirect in a node. */
enum	e_redir
{
	NO_REDIR,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
};

/* Enum for classifying the type of data that the node has. */
enum	e_type
{
	NON_VALID,
	STR,
	REDIR,
	HERE,
	PIPE,
	BUILTIN,
	DEL,
	FIL,
	FLAG,
	VAR,
};

/* Enum for file descriptors. */
enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
};
#endif
