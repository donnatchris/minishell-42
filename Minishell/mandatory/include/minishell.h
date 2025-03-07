/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:48:46 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 10:39:13 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

// headers
# include "../../libft/headers/libft_H/libft.h"
# include "../../libft/headers/ft_printf_H/ft_printf.h"
# include "../../dclst/dclst.h"
# include "minishell_defines.h"

// prototypes
/* ************************************************************************** */
/*										builtins							  */
/* ************************************************************************** */
// env.c
int			env_cmd(char **args, char **envp);
// echo.c
int			echo_cmd(char **args, char **envp);
// cd.c
int			cd_cmd(char **args, char ***envp, t_general *gen);
// export.c
int			export_cmd(char **args, char ***envp);
// pwd.c
int			pwd_cmd(char **args, char **envp);
// unset.c
int			unset_cmd(char **args, char ***envp);
// exit.c
void		exit_cmd(char **args, char **envp, t_general *gen);
/* ************************************************************************** */
/*										env									  */
/* ************************************************************************** */
// read_env.c
size_t		count_env_size(char **envp);
char		**find_env_var(const char *var, char **envp);
char		*ft_getenv(const char *var, char **envp);
int			compare_env_vars(const char *s1, const char *s2);
// write_env.c
char		**ft_realloc_env(char ***envp, char *new_entry);
int			create_env_var_void(const char *key, char sep, char ***envp);
int			create_env_var(const char *key, char sep,
				const char *value, char ***envp);
int			update_env_var(const char *key,
				char sep, const char *value, char ***envp);
char		**copy_env(char **envp);
/* ************************************************************************** */
/*										executor							  */
/* ************************************************************************** */
// cmd_execve.c
int			execve_cmd(char *cmd, char **args, char **envp);
// exec_cmd.c
int			exec_cmd(t_dclst *node, char ***envp, t_general *gen);
// exec_leaf.c
int			exec_leaf(t_dclst *node, char ***envp, t_general *gen);
// exec_tree.c
int			exec_tree(t_tree *tree, char ***envp, t_general *gen);
// extract_arguments.c
char		**extract_args(t_dclst *node, char **envp, t_general *gen);
/* ************************************************************************** */
/*										operators							  */
/* ************************************************************************** */
// parenthesis.c
int			run_parenthesis(t_tree *tree, char ***envp, t_general *gen);
// pipe.c
int			pipe_operator(t_tree *tree, char ***envp, t_general *gen);
int			writing_proc(int fd[], t_tree *tree, char ***envp, t_general *gen);
int			reading_proc(int fd[], t_tree *tree, char ***envp, t_general *gen);
// redirection_in.c
void		end_redir_in(int stdin_backup);
int			redir_in(t_dclst *node, char ***envp, t_general *gen);
// redirection_out.c
void		end_redir_out(int stdout_backup);
int			redir_out(t_dclst *node, char ***envp, t_general *gen);
// heredoc.c
void		redir_heredoc_read(int pipefd[2],
				char **delimiters, char **envp, t_general *gen);
int			redir_heredoc(t_dclst *node, char ***envp, t_general *gen);
/* ************************************************************************** */
/*										parser								  */
/* ************************************************************************** */
// binary_tree.c
t_tree		*create_tree(t_dclst *first, t_dclst *last);
// check_synthax.c
int			check_syntax(t_dclst **head, t_general *gen, int mode);
// get_token1.c
int			get_token(char **ps, char *es, char **q, char **eq);
// get_token2.c
int			get_single_quote(char **s, char *es);
int			double_quote(char **s, char *es);
int			get_semi_colon(char **s);
int			get_amperstand(char **s, char *es);
int			get_vertical_bar(char **s);
// lexer.c
t_dclst		**tokenize(char *input);
/* ************************************************************************** */
/*										signals								  */
/* ************************************************************************** */
// signal_handler.c
void		init_signals(void);
void		signal_handler(int signum);
void		ignore_signals(void);
void		heredoc_signals(void);
void		heredoc_signal_handler(int signum);
/* ************************************************************************** */
/*									text_transformer						  */
/* ************************************************************************** */
// dollar_manager.c
char		*replace_each_dollar(char *str, char **envp, int exit_status);
char		*manage_dollar(t_token *token, char **envp, int exit_status);
// filenames_extraction.c
char		**extract_matching_filenames(char *arg, char **file_array);
// filenames_searcher.c
int			is_matching_filename(char *pattern, char *filename);
// get_files_in_dir.c
char		**get_files_in_dir(char *path, int mode);
// wildcard_manager.c
char		*manage_wildcards(char *arg, t_dclst *node, t_general *gen);
/* ************************************************************************** */
/*										utils								  */
/* ************************************************************************** */
// delete_functions.c
void		delete_str_tab(char **tab);
void		delete_tree(t_tree *root);
void		delete_cmd_line(t_general *gen);
void		delete_general(t_general *gen);
// error_msg.c
int			ft_perror(char *cmd, char *msg);
int			shell_err_msg(char *cmd, char *msg);
int			shell_error_quote(char *cmd, char *msg);
int			open_error(char *filename);
// ft_strtol.c
long		ft_strtol(const char *nptr, char **endptr, int base);
// initialize minishell
t_general	*init_gen(t_general *gen, char **envp, char **av, int ac);
int			change_shlvl(char ***envp);
// node_token_info1.c
int			is_logical_operator(t_dclst *node);
int			is_parenthesis(t_dclst *node);
int			is_eof(t_dclst *node);
int			is_pipe(t_dclst *node);
int			is_tree_branch(t_dclst *node);
// node_token_info2.c
int			is_text(t_dclst *node);
int			is_redir(t_dclst *node);
int			is_heredoc(t_dclst *node);
int			is_redir_in(t_dclst *node);
int			is_redir_out(t_dclst *node);
// node_token_info3.c
int			has_space(t_dclst *node);
// token_error_message.c
int			print_token_error(t_token *token);
// utils_functions.c
char		**ft_realloc_str_array(char **tab, size_t new_size);
char		*cut_name(char *str);
int			is_valid_var_name(char *str);
/* ************************************************************************** */
/*										test								  */
/* ************************************************************************** */
// tests_to_remove.c
void		print_tree(t_tree *root);
void		print_string(char *start, char *end);
void		print_a_token(t_token *token);
void		print_dclst_tokens(t_dclst **head);

#endif