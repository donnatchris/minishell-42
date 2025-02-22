#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

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
int	env_cmd(char **args, char **envp);
// echo.c
int		echo_cmd(char **args, char **envp);
int		newline_flag(char *str);
// cd.c
void	actualize_cd_env(char *oldpwd, char ***envp);
char	*find_actual_dir(void);
char	*find_parent_dir(void);
char	*find_cd_path(char *input, char **envp);
int		cd_cmd(char **args, char ***envp);
// export.c
int		export_cmd(char **args, char ***envp);
// pwd.c
char	*find_next_lowest_var(char *var, char **envp);
void	print_chars(char *start, char *end);
int		print_exp_var_env(char **envp);
int		is_valid_var_name(char *str);
char	*cut_name(char *str);
void	pwd_cmd(char **args, char **envp);
// unset.c
int		my_realloc(void **ptr, int old_size, int new_size);
int		unset_one_env_var(char *key, char ***envp);
int		unset_cmd(char **args, char ***envp);
// exit.c
void	exit_cmd(char **args, char **envp);
/* ************************************************************************** */
/*										env									  */
/* ************************************************************************** */
// read_env.c
size_t	count_env_size(char **envp);
char	**find_env_var(const char *var, char **envp);
char	*ft_getenv(const char *var, char **envp);
// write_env.c
char	**ft_realloc_env(char ***envp, char *new_entry);
int		create_env_var_void(const char *key, char sep, char ***envp);
int		create_env_var(const char *key, char sep, const char *value, char ***envp);
int		update_env_var(const char *key, char sep, const char *value, char ***envp);
char	**copy_env(char **envp);
/* ************************************************************************** */
/*										executor							  */
/* ************************************************************************** */
// cmd_execve.c
char	*find_path_in_PATH(char *cmd, char **path_split);
char	*find_exec_path(char *cmd, char **envp);
int		execute_cmd(char *path, char **args, char **envp);
int		execve_cmd(char *cmd, char **args, char **envp);
// exec_node.c.c
int	exec_node(t_dclst *node, char ***envp);
// extract_cmd_and_args.c
char	**ft_realloc_str_array(char **tab, size_t new_size);
char	**extract_args(t_dclst *node, char **envp);
char	*extract_cmd(t_dclst *node, char **envp);
/* ************************************************************************** */
/*										parser								  */
/* ************************************************************************** */
t_dclst	**tokenize(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);
int		check_syntax(t_dclst **head);
t_tree	*create_tree(t_dclst *first, t_dclst *last);
void	clear_tree(t_tree *root);
void	print_token(t_token *token);
void	print_tree(t_tree *root); // A retirer avant de rendre
void	print_a_token(t_token *token); // A retirer avant de rendre
void	print_dclst_tokens(t_dclst **head); // A retirer avant de rendre
/* ************************************************************************** */
/*										signals								  */
/* ************************************************************************** */

/* ************************************************************************** */
/*										utils								  */
/* ************************************************************************** */
// delete_functions.c
void	delete_str_tab(char **tab);
// dollar_manager.c
char	*find_var_name_end(char *ptr);
char	*replace_a_dollar(char *str, char *doll_pos, char **envp);
char	*replace_each_dollar(char *str, char **envp);
char	*manage_dollar(t_token *token, char **envp);
// error_msg.c
int		print_token_error(t_token *token);
int		ft_perror(char *cmd, char *msg);
int		shell_error_msg(char *cmd, char *msg);
int		shell_error_quote(char *cmd, char *msg);
// initialize minishell
int	change_shlvl(char ***envp);
// ft_strtol.c
long	ft_strtol(const char *nptr, char **endptr, int base);


#endif