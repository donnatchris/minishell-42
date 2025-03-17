/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:48:46 by christophed       #+#    #+#             */
/*   Updated: 2025/03/17 15:09:56 by chdonnat         ###   ########.fr       */
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
int			unset_one_env_var(char *key, char ***envp);
// exit.c
void		exit_cmd(char **args, char **envp, t_general *gen);
/* ************************************************************************** */
/*										env									  */
/* ************************************************************************** */
// read_env.c
size_t		count_array_size(char **envp);
char		**find_env_var(const char *var, char **envp);
char		*ft_getenv(const char *var, char **envp);
int			compare_env_vars(const char *s1, const char *s2);
char		*find_var_name_end(char *ptr);
// write_env.c
char		**ft_realloc_env(char ***envp, char *new_entry);
int			create_env_var(const char *key, char sep, const char *value,
				char ***envp);
int			update_env_var(const char *key,
				char sep, const char *value, char ***envp);
char		**copy_env(char **envp);
/* ************************************************************************** */
/*										executor							  */
/* ************************************************************************** */
// cmd_execve.c
int			execve_cmd(char *cmd, char **args, char **envp, t_general *gen);
// exec_cmd.c
int			exec_cmd(t_dclst *node, t_general *gen);
// exec_leaf.c
int			exec_leaf(t_dclst *node, t_general *gen);
t_dclst		*get_next_heredoc(t_dclst *node);
// exec_tree.c
int			exec_tree(t_tree *tree, t_general *gen);
// extract_arguments.c
char		**extract_args(t_dclst *node, t_general *gen);
// extract_filename.c
char		*extract_filename(t_dclst *node, t_general *gen);

/* ************************************************************************** */
/*										operators							  */
/* ************************************************************************** */
// parenthesis.c
int			run_parenthesis(t_tree *tree, t_general *gen);
// pipe.c
int			pipe_operator(t_tree *tree, t_general *gen);
// redirection_in.c
int			redir_in(t_dclst *node, t_general *gen);
// redirection_out.c
int			redir_out(t_dclst *node, t_general *gen);
// heredo_delimiter.c
t_delim		*find_delimiter(t_dclst *node);
// heredoc.c
int			create_heredoc(t_dclst *node, t_general *gen);
int			redir_heredoc(void);
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
void		main_signal_handler(int signum);
/* ************************************************************************** */
/*									text_transformer						  */
/* ************************************************************************** */
// dollar_manager.c
char		*replace_each_dollar(char *str, t_general *gen);
char		*manage_dollar(t_token *token, t_general *gen);
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
// delete_functions1.c
void		delete_cmd_line(t_general *gen);
void		delete_general(t_general *gen);
void		delete_before_close(t_general *gen);
// delete_functions2.c
void		delete_delim(t_delim *delim);
void		delete_str_tab(char **tab);
void		delete_tree(t_tree *root);
// error_messages1.c
int			ft_perror(char *cmd, char *msg);
int			shell_err_msg(char *cmd, char *msg);
int			shell_error_quote(char *cmd, char *msg);
int			open_error(char *filename);
// error_messages2.c
int			print_token_error(t_token *token);
int			print_parenthesis_error(void);
void		execve_err_msg(char *cmd);
void		warning_msg(char *delimiter, int n_line);
// ft_strtol.c
long		ft_strtol(const char *nptr, char **endptr, int base);
// get_next_node.c
t_dclst		*get_next_heredoc(t_dclst *node);
t_dclst		*get_next_cmd(t_dclst *node);
t_dclst		*get_next_redir(t_dclst *node);
// initialize minishell
t_general	*init_gen(t_general *gen, char **envp, char **av, int ac);
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
int			is_filename(t_dclst *node);
int			is_and_or(t_dclst *node);
int			is_semicolon(t_dclst *node);
// utils_functions.c
char		**ft_realloc_str_array(char **tab, size_t new_size);
char		*cut_name(char *str);
int			is_valid_var_name(char *str);

#endif