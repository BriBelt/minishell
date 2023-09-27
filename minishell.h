/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:58 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/27 15:59:31 by bbeltran         ###   ########.fr       */
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

/*		
 *	GLOBAL VARIABLE	
 *						*/
t_global	g_global;
/*		
 *		readline	
 *						*/
void		rl_replace_line(const char *text, int clear_undo);
void		minishell_exe(t_shell *mini, int in, int out);
/*
 * 		parser			
 * 						*/
t_lexer		**ft_parser(t_shell *mini, char *rd);
/*		
 *		space_split		
 *						*/
t_basic		**create_space_sep(char *rd);
/*		
 *		quote_split		
 *						*/
int			quote_list_checker(t_basic **list);
t_basic		**create_quote_sep(t_basic **space_sep);
/*		
 *	var_expand_utils
 *						*/
int			total_node_len(char *data, t_shell *mini);
void		set_first_quote2(char *data, int *count, int *first, int *i);
char		*split_variables(char *data, int *i);
int			symbol_count(char *data);
char		*more_than_one_expand(char *data, t_shell *mini);
/*		
 *		var_expand		
 *						*/
char		*split_variables(char *data, int *i);
char		*found_symbol(char *data, t_shell *mini);
void		change_node_var(t_basic **pipes, t_shell *mini);
/*		
 *		node_join		
 *						*/
t_lexer		**final_lexer(t_basic **lst);
/*		
 *		t_basic			
 *						*/
t_basic		*new_create_node(char *content, int join);
void		ft_basic_insert(t_basic	**lst, char *content, size_t join);
/*		
 *		list_utils		
 *						*/
t_lexer		**create_lexer(t_basic **basic);
t_lexer		*ft_lexernew(char *content, int i, size_t join);
void		ft_lexer_insert(t_lexer	**lst, char *ct, int i, size_t join);
/*		
 *		typesort		
 *						*/
int			is_builtin(char *content);
int			is_command(char *content);
int			redirect_or_pipe(char *content);
void		def_type(t_lexer **lst);
/*		
 *		typesort_utils		
 *						*/
int			flag_or_envar(char *content, int quote_type);
int			is_file(char *content);
void		is_file_type(t_lexer **lexer);
/*		
 *		free_utils		
 *						*/
void		free_2d_array(char **array);
void		free_t_lexer(t_lexer **lst);
void		free_t_basic(t_basic **lst);
void		free_t_command(t_command **lst);
void		free_t_red(t_red **lst);
/*		
 *			t_red			
 *						*/
int			redirect_type(char *data);
t_red		**create_redir_list(t_lexer	*curr);
/*		
 *		t_command - execution_utils
 *									*/
t_command	**create_command_list(t_lexer **lexer);
/*		
 *		t_command_utils
 *						*/
char		**get_args(t_lexer *curr);
/*		
 *			pwd				
 *						*/
void		ft_pwd(void);
/*		
 *			echo			
 *						*/
void		ft_echo(t_command *node);
/*			
 *			exit			
 *						*/
void		ft_exit(t_shell *mini);
/*		
 *			cd				
 *						*/
void		ft_cd(t_command *node);
/*			
 *			env				
 *						*/
void		ft_env(t_command *node, char **envp);
/*			
 *			unset			
 *						*/
int			array_size(char **envp, char *desired_path);
char		**ft_unset(char **envp, t_command *node);
/*		
 *		export_utils	
 *						*/
int			find_size_envp(char **envp, int found);
int			check_for_export(char *data);
/*			
 *			export
 *						*/
void		print_sort_env(char **envp);
char		**ft_export(char **envp, t_command *node);
/*			
 *			builtins		
 *						*/
void		exec_one_builtin(t_shell *mini, t_pipex pipex);
int			builtin_arg(t_command *node);
int			call_builtins(t_command *node, t_shell *mini);
/*		
 *		path_utils		
 *						*/
int			search_in_envar(char *search, char **envars);
char		**get_paths(t_shell *mini, char *pathname);
char		*expand_envar(char *data, t_shell *mini);
char		**copy_envp(char **envp);
/*		
 *		quotes		
 *						*/
void		clean_quotes(t_basic **pipes);
char		*split_quote_sens(char *data, size_t *i);
char		*handle_quotes(char	*rd, size_t	*i);
/*		
 *		quote_utils		
 *						*/
int			quote_type(char c);
t_quote		*initialize_t_quote(void);
void		count_quotes(char *rd, int *i, t_quote *h);
/*		
 *		redirections	
 *						*/
t_basic		**redirect_separate(t_basic **closed_q);
int			check_redirects(t_lexer **lex);
/*		
 *		redir_utils		
 *						*/
int			valid_redirects(char *data);
int			first_redirect(char *data);
/*		
 *			pipes			
 *						*/
t_basic		**pipe_separate(t_basic **r_basic);
int			check_pipes(t_lexer **lex);
/*		
 *		heredoc_utils	
 *						*/
t_lexer		*check_for_heredoc(t_lexer **lexer);
char		*find_delimiter(t_lexer **lexer);
int			heredoc_or_input(t_red **redirects);
int			open_heredoc_file(t_shell *mini);
int			here_counter(t_command **commands);
/*		
 *			heredoc			
 *						*/
int			open_heredoc_file(t_shell *mini);
int			here_doc_exe(t_command **commands);
int			here_counter(t_command **commands);
int			count_input_heredocs(t_command **commands);
/*		
 *		exe_redirect		
 *						*/
t_red		*last_redirect(t_red **redirect, int in_or_out);
int			check_for_children(t_lexer **lexer);
int			check_redir_access(t_lexer **lexer);
/*		
 *		execution		
 *						*/
void		command_executor(t_shell *mini, t_command **commands);
void		executor(t_shell *mini);
/*		
 *	execution_utils		
 *						*/
int			is_space(char c);
void		delete_all_files(int in_heredocs);
t_pipex		pipex_init(void);
void		wait_for_child(t_pipex pipex, int count, t_shell *mini);
char		**find_all_del(t_command **commands);
/*		
 *		children_utils		
 *						*/
void		child_out_fd(t_pipex pipex, int i, int child_num);
char		*get_child_path(t_command *command, t_shell *mini);
int			is_path(char *arg);
int			found_redirect_type(t_red **redirect, int type);
void		get_file_des(t_pipex *pipex, t_red **redirect);
/*		
 *		command_utils		
 *						*/
int			command_counter(t_command **commands);
char		*find_comm_path(t_shell *mini, char *data);
/*		
 *		children			
 *						*/
void		only_child(t_pipex pipex, t_command *cmd, t_shell *mini);
t_pipex		first_child(t_pipex pipex, t_command *cmd, t_shell *mini);
t_pipex		middle_child(t_pipex pipex, t_command *cmd, t_shell *mini, int i);
t_pipex		last_child(t_pipex pipex, t_command *cmd, t_shell *mini, int i);
/*		
 *		signals				
 *						*/
int			ft_heredoc_signal(int here_child);
void		signal_handler(int sig);
#endif
