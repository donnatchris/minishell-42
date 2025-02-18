#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_cd -Wall -Werror -Wextra cd.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

// Function to get an environement variable from the key
char	*get_env_value(const char *key, char **envp)
{
	int		i;
	size_t	len;
	char	*value;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], len) == 0 && envp[i][len] == '=')
		{
			value = envp[i] + len + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	cd_cmd(const char *path, char **envp)
{
	// char	old_pwd[PATH_MAX];
	// char	cwd[PATH_MAX];

	// if (!getcwd(old_pwd, sizeof(old_pwd)))
	// 	perror("cd error: getcwd failed");
	if (!path || *path == '\0')
	{
		path = get_env_value("HOME", envp);
		if (!path)
			return (ft_printf("cd: HOME NOT SET "));
	}
	if (chdir(path) == -1)
		return (perror("cd error"), -1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 2)
		return (ft_printf("one arg nedded"), 1);
	// char	*res;
	// res = get_env_value(av[1], envp);
	// if (!res)
	// 	ft_printf("env_var not found\n");
	// else
	// 	ft_printf("%s\n", res);
	cd_cmd(av[1], envp);
	return (0);
}