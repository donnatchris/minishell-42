#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

// headers
# include "../../libft/headers/libft_H/libft.h"
# include "../../libft/headers/ft_printf_H/ft_printf.h"
# include "../../dclst/dclst.h"
# include "minishell_defines.h"

// prototypes
/* ************************************************************************** */
/*										parser								  */
/* ************************************************************************** */
t_dclst	**tokenize(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);
int		check_syntax(t_dclst **head);
t_tree	*create_tree(t_dclst *first, t_dclst *last);
void	clear_tree(t_tree *root);
void	print_tree(t_tree *root); // A retirer avant de rendre
void	print_a_token(t_token *token); // A retirer avant de rendre
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
/*										builtins							  */
/* ************************************************************************** */
// env.c
void	env_cmd(char **args, char **envp);
// echo.c
void	echo_cmd(char **args, char **envp);
int     newline_flag(char *str);
// cd.c
void	actualize_cd_env(char *oldpwd, char ***envp);
char	*find_actual_dir(void);
char	*find_parent_dir(void);
char	*find_cd_path(char *input, char **envp);
int		cd_cmd(char **args, char ***envp);
// export.c
int		export_cmd(char **args, char ***envp);
// pwd.c
void	pwd_cmd(char **args, char **envp);
/* ************************************************************************** */
/*										utils								  */
/* ************************************************************************** */
// dollar_manager.c
char	*find_var_name_end(char *ptr);
char	*replace_a_dollar(char *str, char *doll_pos, char **envp);
char	*replace_each_dollar(char *str, char **envp);
char	*manage_dollar(t_token *token, char **envp);
// delete_functions.c
void	delete_str_tab(char **tab);

// A SUPPRIMER AVANT DE RENDRE
void	print_dclst_tokens(t_dclst **head);
void	print_a_token(t_token *token);

#endif