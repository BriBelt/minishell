/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:01:20 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/13 12:29:38 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# define PIPE_ERR "Syntax error near unexpected token \'|\'\n"
# define REDIR_ERR "Syntax error near unexpected redirect token\n"
# define QUOTE_ERR "Syntax error: Unclosed quotes\n"

enum	e_redir
{
	NO_REDIR,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
};

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

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
};
#endif
