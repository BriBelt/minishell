/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:22:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/14 17:42:48 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
/* Change defines for enum structures, one for types and one for types of
 * rediredirect. */
# define STR 1 
# define REDIR 2 
# define PIPE 3
# define BUILTIN 4
# define COMMAND 5
# define FIL 6
# define FLAG 7
# define VAR 8
#include <stdio.h>

typedef	struct	s_basic
{
	char		*data;
	size_t		join;
	struct	s_basic	*next;
}				t_basic;

typedef	struct	s_lexer
{
	char		*data;
	int			index;
	int			type;
	size_t		join;
	struct	s_lexer		*next;
}				t_lexer;

typedef	struct	s_shell
{
	char	**envp;
	t_lexer	**lex;
}				t_shell;

typedef struct	s_quote
{
	int		normal;
	int		count;
	int		start;
	int		first;
	int		end;
}				t_quote;

#endif
