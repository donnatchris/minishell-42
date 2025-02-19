#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_cd -Wall -Werror -Wextra cd.c ../env/read_env.c ../env/write_env.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

// Function to update or create PWD and OLDPWD in the environment variables
// Returns 0 on success, -1 on failure
void	actualize_cd_env(char *oldpwd, char *pwd, char ***envp)
{
	if (update_env_var("OLDPWD", oldpwd, *envp) == -1)
		ft_putstr_fd("cd: failed to create OLDPWD\n", 2);
	if (update_env_var("PWD", pwd, *envp) == -1)
		ft_putstr_fd("cd: failed to create PWD\n", 2);
}

// Function to go the actual dir
// Returns a pointer to the path
// Returns NULL on failure
char	*find_actual_dir(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("cd: getcwd failed"), NULL);
	return (ft_strdup(pwd));
}

// Function to change directory to the parent directory
// Returns a pointer to the path
// Returns NULL on failure
char	*find_parent_dir(void)
{
	char	pwd[PATH_MAX];
	char	*ptr;

	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("cd: getcwd failed"), NULL);
	ptr = ft_strrchr(pwd, '/');
	if (ptr == NULL)
		return (perror("cd: invalid path"), NULL);
	if (ptr == pwd)
		return (ft_strdup("/"));
	else
		*ptr = '\0';
	return (ft_strdup(pwd));
}

// Function to find the path for the cd command
// Returns a pointer to the path
// Returns NULL on failure
char	*find_cd_path(char *input, char **envp)
{
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
		return (ft_putstr_fd("cd: HOME NOT SET", 2), NULL);
	if (!input || *input == '\0')
		input = home;
	if (!ft_strncmp(input, "..", 2) && ft_strlen(input) == 2)
		return (find_parent_dir());
	else if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
		return (find_actual_dir());
	else if (input[0] == '~')
		return (ft_strjoin(home, input + 1));
	else if (!ft_strncmp(input, "-", 1))
		return (ft_strdup(ft_getenv("OLDPWD", envp)));
	else
		return (ft_strdup(input));
}

// Function to change directorylike the cd command
// and properly update the environment variables
// Returns 0 on success, -1 on failure
int	cd_cmd(char *path, char **envp)
{
	char	pwd[PATH_MAX];
	char	*new_pwd;

	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("cd: getcwd failed"), -1);
	new_pwd = find_cd_path(path, envp);
	if (!new_pwd)
		return (-1);
	if (chdir(new_pwd) == -1)
		return  (free(new_pwd), perror("cd error"), -1);
	actualize_cd_env(pwd, new_pwd, &envp);
	free(new_pwd);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**new_envp;

// 	if (ac != 2)
// 		return (ft_printf("one arg needed"), 1);
// 	new_envp = copy_env(envp);
// 	if (!new_envp)
// 		return (perror("copy_env malloc failed"), 1);
// 	cd_cmd(av[1], new_envp);
// 	ft_printf("PWD = %s\n", ft_getenv("PWD", new_envp)); // debug
// 	ft_printf("OLDPWD = %s\n", ft_getenv("OLDPWD", new_envp)); // debug
// 	delete_env(new_envp);
// 	return (0);
// }