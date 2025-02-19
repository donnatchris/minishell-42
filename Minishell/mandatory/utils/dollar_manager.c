/*****************************************************************************
COMPILE WITH:
gcc -o test_replace_each_dollar -Wall -Werror -Wextra dollar_manager.c ../src/env/read_env.c ../src/env/write_env.c ../../dclst/dclst1.c ../../dclst/dclst2.c ../../dclst/dclst3.c -L../../libft -lft_inc -I../../libft/headers/libft_H
*****************************************************************************/

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
		return (ft_putstr_fd("replace_a_dollar : ft_strdup failed", 2), NULL);
	value = ft_getenv(var, envp);
	if (!value)
		value = "";
	free(var);
	str[doll_pos - str] = '\0';
	temp_str = ft_strjoin(str, value);
	if (!temp_str)
		return (ft_putstr_fd("replace_a_dollar : ft_strjoin failed", 2), NULL);
	new_str = ft_strjoin(temp_str, remainder);
	free(temp_str);
	if (!new_str)
		return (ft_putstr_fd("replace_a_dollar : ft_strjoin failed", 2), NULL);
	return (new_str);
}

// Function to replace every $ of a string with the corresponding variable in the envp
// Returns a pointer to the new string or NULL if it fails
char	*replace_each_dollar(char *str, char **envp)
{
	char	*ptr;
	char	*res;

	if (!str || !envp)
		return (ft_putstr_fd("replace_each_doll : invalid arg", 2), NULL);
	ptr = ft_strchr(str, '$');
	res = ft_strdup(str);
	if (!res)
		return (ft_putstr_fd("replace_each_doll : ft_strdup failed", 2), NULL);
	while (ptr)
	{
		str = res;
		res = replace_a_dollar(str, ptr, envp);
		free(str);
		if (!res)
			return (NULL);
		ptr = ft_strchr(res, '$');
	}
	return (res);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	if (ac != 2)
		return (ft_printf("need one argument"), 1);
	str = replace_each_dollar(av[1], envp);
	if (!str)
		return (ft_printf("la chaine est vide \n"), 1);
	ft_printf("%s", str);
	free(str);
	return (0);
}
