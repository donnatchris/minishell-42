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
int			newline_flag(char *str);
// cd.c
void	    actualize_cd_env(char *oldpwd, char ***envp, t_general *gen, char *pwd);
char		*find_actual_dir(void);
char		*find_cd_path(char *input, char **envp, char *home, char *old);
int			cd_cmd(char **args, char ***envp, t_general *gen);
// export.c
int			export_cmd(char **args, char ***envp);
// pwd.c
int			pwd_cmd(char **args, char **envp);
// unset.c
int			my_realloc(void **ptr, int old_size, int new_size);
int			unset_one_env_var(char *key, char ***envp);
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
int 		compare_env_vars(const char *s1, const char *s2);
// write_env.c
char		**ft_realloc_env(char ***envp, char *new_entry);
int			create_env_var_void(const char *key, char sep, char ***envp);
int			create_env_var(const char *key, char sep, const char *value, char ***envp);
int			update_env_var(const char *key, char sep, const char *value, char ***envp);
char		**copy_env(char **envp);
/* ************************************************************************** */
/*										executor							  */
/* ************************************************************************** */
// cmd_execve.c
int			execve_cmd(char *cmd, char **args, char **envp);
// exec_cmd.c
int			exec_cmd(t_dclst *node, char ***envp, t_general *gen);
// exec_leaf.c
int			exec_leaf(t_dclst *node, char*** envp, t_general *gen);
// exec_tree.c
int			exec_tree(t_tree *tree, char ***envp, t_general *gen);
// extract_arguments.c
char		**extract_args(t_dclst *node, char **envp, t_general *gen);
/* ************************************************************************** */
/*										operators							  */
/* ************************************************************************** */
// parenthesis.c
int			mini_minishell(t_dclst **head, char **envp, t_general *gen);
int			run_parenthesis(t_tree *tree, char ***envp, t_general *gen);
// pipe.c
int			pipe_operator(t_tree *tree, char ***envp, t_general *gen);
int			writing_proc(int fd[], t_tree *tree, char ***envp, t_general *gen);
int			reading_proc(int fd[], t_tree *tree, char ***envp, t_general *gen);
// redirection_in.c
void        end_redir_in(int stdin_backup);
int         redir_in(t_dclst *node, char ***envp, t_general *gen);
// redirection_out.c
void		end_redir_out(int stdout_backup);
int			redir_out(t_dclst *node, char ***envp, t_general *gen);
// heredoc.c
void		redir_heredoc_read(int pipefd[2], char *delimiter, char **envp, int exit_status);
int         redir_heredoc(t_dclst *node, char ***envp, t_general *gen);
/* ************************************************************************** */
/*										parser								  */
/* ************************************************************************** */
// binary_tree.c
void		print_tree(t_tree *root);			// A retirer avant de rendre
int			find_tree_node_type(t_token *token);
t_tree		*create_tree_node(t_dclst *list_node);
t_dclst		*find_lowest_priority(t_dclst *first_node, t_dclst *last_node);
t_tree		*create_tree(t_dclst *first, t_dclst *last);
// check_synthax.c
int			check_syntax(t_dclst **head, t_general *gen, int mode);
// get_token.c
int			get_single_quote(char **s, char *es);
int			double_quote(char **s, char *es);
int			get_semi_colon(char **s);
int			get_amperstand(char **s, char *es);
int			get_vertical_bar(char **s);
int			get_parenthesis(char **s, char *es);
int			get_angle_bracket(char **s);
int			get_symbol(char **s, char *es);
int			get_word(char **s, char *es);
int			get_token(char **ps, char *es, char **q, char **eq);
// lexer.c
void		affect_tokens_priority(t_dclst **head);
void		null_terminate_token(t_dclst **head);
int			tokenize_to_dclst(char *input, t_dclst **head);
t_dclst		**tokenize(char *input);
// tests_to_remove.c							// A retirer avant de rendre
void		print_tree(t_tree *root); 			// A retirer avant de rendre
void		print_a_token(t_token *token); 		// A retirer avant de rendre
void		print_dclst_tokens(t_dclst **head); // A retirer avant de rendre
/* ************************************************************************** */
/*										signals								  */
/* ************************************************************************** */
// signal_handler.c
void		init_signals(void);
void	    signal_handler(int signum);
/* ************************************************************************** */
/*									wildcard_manager						  */
/* ************************************************************************** */
char		**extract_matching_filenames(char *arg, char **file_array);
char		**get_files_in_dir(char *path, int mode);
char		*manage_wildcards(char *arg, t_dclst *node, t_general *gen);
/* ************************************************************************** */
/*										utils								  */
/* ************************************************************************** */
// delete_functions.c
void		delete_str_tab(char **tab);
void		delete_tree(t_tree *root);
void		delete_cmd_line(t_general *gen);
void		delete_general(t_general *gen);
// dollar_manager.c
char		*find_var_name_end(char *ptr);
char		*replace_a_dollar(char *str, char *doll_pos, char **envp);
char		*replace_with_exit_status(char *str, char *doll_pos, char **envp, int exit_status);
char		*replace_each_dollar(char *str, char **envp, int exit_status);
char		*manage_dollar(t_token *token, char **envp, int exit_status);
// error_msg.c
int			print_token_error(t_token *token);
void		print_token(t_token *token);
int			ft_perror(char *cmd, char *msg);
int			shell_error_msg(char *cmd, char *msg);
int			shell_error_quote(char *cmd, char *msg);
int			open_error(char *filename);
// ft_strtol.c
long		ft_strtol(const char *nptr, char **endptr, int base);
// initialize minishell
t_general	*init_gen(t_general *gen, char **envp, char **av, int ac);
int			change_shlvl(char ***envp);
// node_token_info.c
int			has_space(t_dclst *node);
int			is_text(t_dclst *node);
int			is_redir(t_dclst *node);
int			is_heredoc(t_dclst *node);
int			is_redir_in(t_dclst *node);
int			is_redir_out(t_dclst *node);
int			is_logical_operator(t_dclst *node);
int			is_parenthesis(t_dclst *node);
int 		is_eof(t_dclst *node);
int			is_pipe(t_dclst *node);
int			is_tree_branch(t_dclst *node);
// utils_functions.c
char		**ft_realloc_str_array(char **tab, size_t new_size);
char		*cut_name(char *str);
int			is_valid_var_name(char *str);

#endif