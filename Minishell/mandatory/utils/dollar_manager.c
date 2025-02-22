#include "../include/minishell.h"

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
char	*replace_a_dollar(char *str, char *doll_pos, char **envp)
{
	char			*var;
	char			*value;
	char			*remainder;
	char			*temp_str;
	char			*new_str;

	if (!str || !envp)
		return (NULL);
	remainder = find_var_name_end(doll_pos + 1);
	var = ft_substr(str, doll_pos - str + 1, (remainder - str - (doll_pos - str)) - 1);
	if (!var)
		return (shell_error_msg("replace_a_dollar", "ft_strdup failed"), NULL);
	value = ft_getenv(var, envp);
	if (!value)
		value = "";
	free(var);
	str[doll_pos - str] = '\0';
	temp_str = ft_strjoin(str, value);
	if (!temp_str)
		return (shell_error_msg("replace_a_dollar", "ft_strjoin failed"), NULL);
	new_str = ft_strjoin(temp_str, remainder);
	free(temp_str);
	if (!new_str)
		return (shell_error_msg("replace_a_dollar", "ft_strjoin failed"), NULL);
	return (new_str);
}

// Function to replace every $ of a string with the corresponding variable in the envp
// Returns a pointer to the new string or NULL if it fails
char	*replace_each_dollar(char *str, char **envp)
{
	char	*ptr;
	char	*res;

	if (!str || !envp)
		return (shell_error_msg("replace_each_doll", "invalid arg"), NULL);
	ptr = ft_strchr(str, '$');
	res = ft_strdup(str);
	if (!res)
		return (shell_error_msg("replace_each_doll", "ft_strdup failed"), NULL);
	while (ptr)
	{
		ptr = ft_strchr(res, '$');
		str = res;
		res = replace_a_dollar(str, ptr, envp);
		free(str);
		if (!res)
			return (NULL);
		ptr = ft_strchr(res, '$');
	}
	return (res);
}

// Function to manage the $ in a token
// Returns a pointer to the new string or NULL if it fails
char	*manage_dollar(t_token *token, char **envp)
{
	char	*str;

	if (!token || !envp || !token->start)
		return (ft_putstr_fd("manage_dollar : invalid arg", 2), NULL);
	// if (token->type < TOKEN_STRING || token->type > TOKEN_LITTERAL)
	// 	return (ft_putstr_fd("manage_dollar : invalid token type", 2), NULL);
	if (token->type != TOKEN_STRING && token->type != TOKEN_WORD)
		str = ft_strdup(token->start);
	else
		str = replace_each_dollar(token->start, envp);
	if (!str)
		return (NULL);
	return (str);
}
