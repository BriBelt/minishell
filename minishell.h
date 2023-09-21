/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/21 15:03:32 by bbeltran         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"

void		rl_replace_line(const char *text, int clear_undo);
t_global	g_global;
void		minishell_exe(t_shell *mini, int in, int out);
/*		parser			*/
t_lexer		**ft_parser(t_shell *mini, char *rd);
/*		space_split		*/
t_basic		**create_space_sep(char *rd);
/*		quote_split		*/
int			quote_list_checker(t_basic **list);
t_basic		**create_quote_sep(t_basic **space_sep);
/*		var_expand		*/
void		change_node_var(t_basic **pipes, t_shell *mini);
/*		node_join		*/
t_lexer		**final_lexer(t_basic **lst);
/*		t_basic			*/
t_basic		*new_create_node(char *content, int join);
void		ft_basic_insert(t_basic	**lst, char *content, size_t join);
//t_basic	**create_basic_lst(char *rd);
/*		list_utils		*/
t_lexer		**create_lexer(t_basic **basic);
t_lexer		*ft_lexernew(char *content, int i, size_t join);
void		ft_lexer_insert(t_lexer	**lst, char *ct, int i, size_t join);
/*		typesort		*/
int			is_builtin(char *content);
int			is_command(char *content);
int			redirect_or_pipe(char *content);
void		def_type(t_lexer **lst);
/*		typesort_utils		*/
int			flag_or_envar(char *content, int quote_type);
int			is_file(char *content);
void		is_file_type(t_lexer **lexer);
/*		free_utils		*/
void		exit_mode(char *strerror, int errornum);
void		free_2d_array(char **array);
void		free_t_lexer(t_lexer **lst);
void		free_t_basic(t_basic **lst);
void		free_t_command(t_command **lst);
void		free_t_red(t_red **lst);
/*		t_red				*/
int			redirect_type(char *data);
t_red		**create_redir_list(t_lexer	*curr);
/*		t_command - execution_utils			*/
t_command	**create_command_list(t_lexer **lexer);
/*		pwd				*/
void		ft_pwd(void);
/*		echo			*/
void		ft_echo(t_command *node);
/*		exit			*/
void		ft_exit(t_shell *mini);
/*		cd				*/
void		ft_cd(t_command *node);
/*		env				*/
void		ft_env(t_command *node, char **envp);
/*		unset			*/
int			array_size(char **envp, char *desired_path);
char		**ft_unset(char **envp, t_command *node);
/*		export			*/
void		print_sort_env(char **envp);
char		**ft_export(char **envp, t_command *node);
/*		builtins		*/
char		*str_tolow(char *str);
int			builtin_arg(t_command *node);
int			call_builtins(t_command *node, t_shell *mini);
/*		path_utils		*/
int			search_in_envar(char *search, char **envars);
char		**get_paths(t_shell *mini, char *pathname);
char		*expand_envar(char *data, t_shell *mini);
char		**copy_envp(char **envp);
/*		quotes		*/
t_quote		*initialize_t_quote(void);
void		check_closed_quotes(t_basic **pipes);
void		clean_quotes(t_basic **pipes);
char		*split_quote_sens(char *data, size_t *i);
char		*handle_quotes(char	*rd, size_t	*i);
/*		quote_utils		*/
int			quote_type(char c);
/*		redirections	*/
t_basic		**redirect_separate(t_basic **closed_q);
int			check_redirects(t_lexer **lex);
/*		pipes			*/
t_basic		**pipe_separate(t_basic **r_basic);
int			check_pipes(t_lexer **lex);
/*		heredoc			*/
int			open_heredoc_file(t_shell *mini);
int			here_doc_exe(t_command **commands);
int			here_counter(t_command **commands);
int			count_input_heredocs(t_command **commands);
/*		check_execution		*/
/*		exe_redirect		*/
t_red		*last_redirect(t_red **redirect, int in_or_out);
int			check_for_children(t_lexer **lexer);
int			check_redir_access(t_lexer **lexer);
/*		execution		*/
t_pipex		pipex_init(void);
void		command_executor(t_shell *mini, t_command **commands);
void		executor(t_shell *mini);
/*		execution_utils		*/
t_pipex		pipex_init(void);
void		wait_for_child(t_pipex pipex, int count, t_shell *mini);
/*		children_utils	*/
int			command_counter(t_command **commands);
char		*find_comm_path(t_shell *mini, char *data);
int			found_redirect_type(t_red **redirect, int type);
void		get_file_des(t_pipex *pipex, t_red **redirect);
void		create_pipes(t_command **commands, t_pipex pipex);
/*		children		*/
void		only_child(t_pipex pipex, t_command *cmd, t_shell *mini);
t_pipex		first_child(t_pipex pipex, t_command *cmd, t_shell *mini);
t_pipex		middle_child(t_pipex pipex, t_command *cmd, t_shell *mini, int i);
t_pipex		last_child(t_pipex pipex, t_command *cmd, t_shell *mini, int i);
/*		signals			*/
void		signal_handler(int sig);
#endif
