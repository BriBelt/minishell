/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 18:27:55 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "struct.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "Libft/libft.h"

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
