/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:22:30 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 12:50:34 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>
# include <sys/wait.h>
# include "enum.h"

typedef struct s_global
{
	char	*pwd;
	int		exit_stat;
}				t_global;

typedef struct s_basic
{
	char			*data;
	size_t			join;
	size_t			quote;
	struct s_basic	*next;
}					t_basic;

typedef struct s_lexer
{
	char				*data;
	int					index;
	int					type;
	size_t				join;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_red
{
	enum e_redir	type;
	char			*data;
	struct s_red	*next;
}					t_red;

typedef struct s_command
{
	char				**args;
	t_red				**redirect;
	struct s_command	*next;
}						t_command;

typedef struct s_pipex
{
	pid_t	child_id[1024];
	int		pipes[1024][2];
	int		in_fd;
	int		out_fd;
	int		one_built;
	char	*cmd_path;
}			t_pipex;

typedef struct s_shell
{
	char		**envp;
	t_lexer		**lex;
	t_command	**cmds;
	int			in_heredocs;
	int			curr_heredoc;
}				t_shell;

typedef struct s_quote
{
	int		normal;
	int		count;
	int		start;
	int		first;
	int		end;
}			t_quote;

#endif
