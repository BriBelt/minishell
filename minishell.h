/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/14 17:25:40 by bbeltran         ###   ########.fr       */
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
#include <string.h>
#include "libft/libft.h"

void	minishell_exe(t_shell *mini);
void	ft_pwd(void);
/*		parser			*/
//void	ft_parsing(t_shell *mini, char *rd);
void	ft_parser(t_shell *mini, char *rd);
t_basic	**create_quote_sep(t_basic **space_sep);
/*		t_basic			*/
void	ft_basic_insert(t_basic	**lst, char *content, size_t join);
t_basic	**create_basic_lst(char *rd);
/*		list_utils		*/
t_lexer	**create_lexer(t_basic **basic);
t_lexer	*ft_lexernew(char *content, int i, size_t join);
void	ft_lexer_insert(t_lexer	**lst, char *content, int i, size_t join);
/*		typesort		*/
void	def_type(t_lexer **lst);
/*		typesort_utils		*/
int		flag_or_envar(char *content);
int		is_file(char *content);
/*		free_utils		*/
void	free_2D_array(char **array);
void	free_t_lexer(t_lexer **lst);
void	free_t_basic(t_basic **lst);
/*		echo			*/
void	ft_echo(t_lexer *node, t_shell *mini);
/*		cd				*/
void	ft_cd(t_lexer *node);
/*		env				*/
void	ft_env(char **envp);
/*		unset			*/
int		array_size(char **envp, char *desired_path);
char	**ft_unset(char **envp, t_lexer *node);
/*		export			*/
char	**ft_export(char **envp, t_lexer *node);
/*		builtins		*/
void	call_builtins(t_lexer *node, char **envp, t_shell *mini);
/*		path_utils		*/
int		search_in_envar(char *search, char **envars);
char	**get_paths(char *pathname);
char	*expand_envar(char *data, t_shell *mini);
char	**copy_envp(char **envp);
/*		quotes		*/
t_quote	*initialize_t_quote(void);
void	clean_quotes(t_lexer **lex);
char	*split_quote_sens(char *data, size_t *i);
char	*handle_quotes(char	*rd, size_t	*i);
/*		quote_utils		*/
int		quote_type(char c);
void	set_new_join(t_lexer **first, char *rd);
void	clean_false_join(t_lexer **lex);
/*		redirections	*/
t_basic	**redirect_separate(t_basic **closed_q);
int		check_redirects(t_lexer **lex);
/*		pipes			*/
t_basic	**pipe_separate(t_basic **r_basic);
int		check_pipes(t_lexer **lex);
/*		final_lexer		*/
size_t	nodes_to_join(t_lexer **first);
size_t	new_node_len(t_lexer **first, size_t count);
char	*join_nodes(t_lexer **first, size_t count);
t_lexer	**create_final_lex(t_lexer **lst);

#endif
