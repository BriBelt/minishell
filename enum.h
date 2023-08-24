/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:01:20 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 11:31:00 by bbeltran         ###   ########.fr       */
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
	PIPE,
	BUILTIN,
	COMMAND,
	FIL,
	FLAG,
	VAR 
};
 #endif
