/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:19:05 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:24:54 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the end of a variable name
// Returns a pointer to the end of the variable name or NULL if there is no name
char	*find_var_name_end(char *ptr)
{
	if (!ptr)
		return (NULL);
	if (!ft_isalpha(*ptr) && *ptr != '_')
		return (ptr);
	while (ft_isalnum(*ptr) || *ptr == '_')
		ptr++;
	return (ptr);
}

// Function to replace a $ with variable in a string
// Returns a pointer to the new string or NULL if it fails
char	*replace_a_dollar(char *str, char *doll_p, char **envp)
{
	char			*var;
	char			*value;
	char			*rest;
	char			*temp_str;
	char			*new_str;

	if (!str || !envp)
		return (NULL);
	rest = find_var_name_end(doll_p + 1);
	var = ft_substr(str, doll_p - str + 1, (rest - str - (doll_p - str)) - 1);
	if (!var)
		return (shell_err_msg("replace_a_dollar", "ft_strdup failed"), NULL);
	value = ft_getenv(var, envp);
	if (!value)
		value = "";
	free(var);
	str[doll_p - str] = '\0';
	temp_str = ft_strjoin(str, value);
	if (!temp_str)
		return (shell_err_msg("replace_a_dollar", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, rest);
	free(temp_str);
	if (!new_str)
		return (shell_err_msg("replace_a_dollar", "ft_strjoin failed"), NULL);
	return (new_str);
}

// Function to replace a $? with the last exit status in a string
// Returns a pointer to the new string or NULL if it fails
char	*replace_w_ex_stat(char *str, char *doll_p, char **envp, int ex_stat)
{
	char	*value;
	char	*remainder;
	char	*temp_str;
	char	*new_str;

	if (!str || !envp)
		return (NULL);
	remainder = doll_p + 2;
	value = ft_itoa(ex_stat);
	if (!value)
		return (shell_err_msg("replace_w_ex_stat", "ft_itoa failed"), NULL);
	str[doll_p - str] = '\0';
	temp_str = ft_strjoin(str, value);
	free(value);
	if (!temp_str)
		return (shell_err_msg("replace_w_ex_stat", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, remainder);
	free(temp_str);
	if (!new_str)
		return (shell_err_msg("replace_w_ex_stat", "ft_strjoin failed"), NULL);
	return (new_str);
}

// Function to replace every $ of a string
// with the corresponding variable in the envp
// Returns a pointer to the new string or NULL if it fails
char	*replace_each_dollar(char *str, char **envp, int ex_stat)
{
	char	*ptr;
	char	*res;

	if (!str || !envp)
		return (shell_err_msg("replace_each_doll", "invalid arg"), NULL);
	ptr = ft_strchr(str, '$');
	res = ft_strdup(str);
	if (!res)
		return (shell_err_msg("replace_each_doll", "ft_strdup failed"), NULL);
	while (ptr)
	{
		ptr = ft_strchr(res, '$');
		str = res;
		if (*(ptr + 1) == '?' && *(ptr + 2) == '\0')
			res = replace_w_ex_stat(str, ptr, envp, ex_stat);
		else
			res = replace_a_dollar(str, ptr, envp);
		free(str);
		if (!res)
			return (NULL);
		ptr = ft_strchr(res, '$');
	}
	return (res);
}

// Function to manage the $ in a token
// Takes a token with a non allocated string (start)
// Returns a pointer to the dynamically allocated new string or NULL if it fails
// RETURN MUST BE FREE AFTER USE
char	*manage_dollar(t_token *token, char **envp, int ex_stat)
{
	char	*str;

	if (!token || !envp || !token->start)
		return (shell_err_msg("manage_dollar", "invalid arg"), NULL);
	if (token->type < TOKEN_STRING || token->type > TOKEN_LITTERAL)
		return (shell_err_msg("manage_dollar", "invalid token type"), NULL);
	if (token->type != TOKEN_STRING && token->type != TOKEN_WORD)
	{
		str = ft_strdup(token->start);
		if (!str)
			return (shell_err_msg("manage_dollar", "ft_strdup failed"), NULL);
	}
	else
		str = replace_each_dollar(token->start, envp, ex_stat);
	if (!str)
		return (NULL);
	return (str);
}
