/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:22:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/26 16:26:52 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>
# include <sys/wait.h>
# include "enum.h"

/*	GLOBAL VARIABLE	*/
typedef struct s_global
{
	char	*pwd;
	int		exit_stat;
}				t_global;

/*	Basic list structure that will be used for parsing and the creation of
 *	the lexer.	*/
typedef struct s_basic
{
	char			*data;
	size_t			join;
	size_t			quote;
	struct s_basic	*next;
}					t_basic;

/*	Lexer list structure that will later be used for the command list.	*/
typedef struct s_lexer
{
	char				*data;
	int					index;
	int					type;
	size_t				join;
	struct s_lexer		*next;
}						t_lexer;

/* Redirection list structure that will be inside each node of the command
 * list of the final t_shell structure.	*/
typedef struct s_red
{
	enum e_redir	type;
	char			*data;
	struct s_red	*next;
}					t_red;

/*	Command list structure, that contains the t_red list and will be used
 *	for our final t_shell structure.	*/
typedef struct s_command
{
	char				**args;
	t_red				**redirect;
	struct s_command	*next;
}						t_command;

/*	Pipex structure, used during the execution of commands and multiple
 *	multiple builtins.	*/
typedef struct s_pipex
{
	pid_t	child_id[1024];
	int		pipes[1024][2];
	int		in_fd;
	int		out_fd;
	int		one_built;
	char	*cmd_path;
}			t_pipex;

/* THE shell structure, contains our envp variables, lexer list, command
 * list, and two heredoc variables that will be used during the execution
 * of the heredocs.	*/
typedef struct s_shell
{
	char		**envp;
	t_lexer		**lex;
	t_command	**cmds;
	int			in_heredocs;
	int			curr_heredoc;
}				t_shell;

/*	Just a structure that we use in order to pass norminette. 
 *	Stores numerous variables that we use during our parsing and quote
 *	separation.	*/
typedef struct s_quote
{
	int		normal;
	int		count;
	int		start;
	int		first;
	int		end;
	int		i;
}			t_quote;

/*	Just a structure that we use in order to pass norminette. 
 *	Stores the needed variables for when executing the heredocs.	*/
typedef struct s_here
{
	char	**dels;
	char	*rd;
	char	*name;
	char	*num;
	int		*in_h;
	int		created;
	int		fd;
	int		child;
	int		j;
	int		i;
}			t_here;

/*	Just a structure that we use in order to pass norminette. 
 *	Stores variables that we use during our process of variable 
 *	expansion.	*/
typedef struct s_exvar
{
	char	*expanded;
	char	*final_str;
	char	*no_sym;
	char	*aux;
}				t_exvar;

#endif
