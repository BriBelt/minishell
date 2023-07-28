/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 17:31:17 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "Libft/libft.h"
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

void	minishell_exe(void);
void	ft_pwd(void);
/*		list_utils		*/
t_lexer	**create_list(char **words);
t_lexer	*ft_lexernew(char *content, int i);
void	ft_lexer_insert(t_lexer	**lst, char *content, int i);
/*		typesort		*/
void	def_type(t_lexer **lst);
/*		typesort_utils		*/
int	flag_or_envar(char *content);
int	is_file(char *content);
char	**get_paths(char *pathname);
char	*expand_envar(char *data);
/*		free_utils		*/
void	free_2D_array(char **array);
void	free_list(t_lexer **lst);
#endif
