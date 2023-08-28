/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart32 <jaimmart32@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/28 13:11:10 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"
# include "enum.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include "libft/libft.h"

void	minishell_exe(t_shell *mini);
/*		parser			*/
t_lexer	**ft_parser(t_shell *mini, char *rd);
/*		space_split		*/
t_basic	**create_space_sep(char *rd);
/*		quote_split		*/
int		quote_list_checker(t_basic **list);
t_basic	**create_quote_sep(t_basic **space_sep);
/*		var_expand		*/
void	change_node_var(t_basic **pipes, t_shell *mini);
/*		node_join		*/
t_lexer	**final_lexer(t_basic **lst);
/*		t_basic			*/
t_basic	*new_create_node(char *content, int join);
void	ft_basic_insert(t_basic	**lst, char *content, size_t join);
//t_basic	**create_basic_lst(char *rd);
/*		list_utils		*/
t_lexer	**create_lexer(t_basic **basic);
t_lexer	*ft_lexernew(char *content, int i, size_t join);
void	ft_lexer_insert(t_lexer	**lst, char *content, int i, size_t join);
/*		typesort		*/
int		redirect_or_pipe(char *content);
void	def_type(t_lexer **lst);
/*		typesort_utils		*/
int		flag_or_envar(char *content);
int		is_file(char *content);
void	is_file_type(t_lexer **lexer);
/*		free_utils		*/
void	free_2D_array(char **array);
void	free_t_lexer(t_lexer **lst);
void	free_t_basic(t_basic **lst);
/*		t_red				*/
t_red	**create_redir_list(t_lexer	*curr);
/*		t_command - execution_utils			*/
t_command	**create_command_list(t_lexer **lexer);
/*		pwd				*/
void	ft_pwd(t_command *node);
/*		echo			*/
void	ft_echo(t_command *node);
/*		cd				*/
void	ft_cd(t_command *node);
/*		env				*/
void	ft_env(t_command *node, char **envp);
/*		unset			*/
int		array_size(char **envp, char *desired_path);
char	**ft_unset(char **envp, t_command *node);
/*		export			*/
void	print_sort_env(char **envp);
char	**ft_export(char **envp, t_command *node);
/*		builtins		*/
char	*str_tolow(char *str);
int		call_builtins(t_command *node, t_shell *mini);
/*		path_utils		*/
int		search_in_envar(char *search, char **envars);
char	**get_paths(char *pathname);
char	*expand_envar(char *data, t_shell *mini);
char	**copy_envp(char **envp);
/*		quotes		*/
t_quote	*initialize_t_quote(void);
void	check_closed_quotes(t_basic **pipes);
void	clean_quotes(t_basic **pipes);
char	*split_quote_sens(char *data, size_t *i);
char	*handle_quotes(char	*rd, size_t	*i);
/*		quote_utils		*/
int		quote_type(char c);
/*		redirections	*/
t_basic	**redirect_separate(t_basic **closed_q);
int		check_redirects(t_lexer **lex);
/*		pipes			*/
t_basic	**pipe_separate(t_basic **r_basic);
int		check_pipes(t_lexer **lex);
/*		heredoc			*/
char	*find_delimiter(t_lexer **lexer);
void	here_doc_exe(char *del);
/*		check_execution		*/
/*		exe_redirect		*/
t_red	*last_redirect(t_red **redirect, int in_or_out);

/*		execution		*/
//void	builtin_executor(t_shell *mini);
void	command_executor(t_shell *mini, t_command **commands);
void	executor(t_shell *mini);
#endif
