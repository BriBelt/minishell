/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:22:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 18:25:06 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define STR 1 
# define REDIR 2 
# define PIPE 3
# define BUILTIN 4
# define COMMAND 5
# define FIL 6
# define FLAG 7
# define VAR 8

typedef	struct	s_lexer
{
	char		*data;
	int			index;
	int			type;
	struct	s_lexer		*next;
}				t_lexer;

#endif
