#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_cd -Wall -Werror -Wextra cd.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

// Function to get the value of an environment variable
// Returns a pointer to the value of the variable
// Returns NULL if the variable is not found
char	*ft_getenv(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// Function to reallocate the environment variable array
// Returns a pointer to the new environment array, or NULL on failure
char	**ft_realloc_env(char **envp, size_t new_size)
{
    char	**new_envp;
    size_t	i;

	i = 0;
    new_envp = (char **) malloc(sizeof(char *) * (new_size + 1));
    if (!new_envp)
        return (NULL);
    if (envp)
    {
		while (envp[i])
		{
            new_envp[i] = envp[i];
			i++;
		}
        free(envp);
    }
    new_envp[i] = NULL;
    return (new_envp);
}

// Function to count environment size
// Returns the number of variables in the environment
size_t	count_env_size(char **envp)
{
	size_t	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// Function to add a new variable to the environment
// Returns 0 on success, -1 on failure
int	create_env_var(const char *key, const char *value, char ***envp)
{
	char	*temp;
	char	*new_entry;
	char	**new_envp;
	size_t	size;

	if (!envp || !key || !value)
		return (ft_putstr_fd("create_env_var: invalid arguments\n", 2), -1);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	free(temp);
	size = count_env_size(*envp);
	new_envp = ft_realloc_env(*envp, size + 1);
	if (!new_envp)
		return (free(new_entry), ft_putstr_fd("create_env_var: realloc failed\n", 2), -1);
	new_envp[size] = new_entry;
	new_envp[size + 1] = NULL;
	*envp = new_envp;
	return (0);
}

// Function to find a variable in the environment
// Returns a pointer to the variable in the environment
// so that it can be updated
// Returns NULL if the variable is not found
char	**find_env_var(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

// Function to update an existing variable in the environment
// Returns 0 on success, -1 on failure
int	update_env_var(const char *key, const char *value, char **envp)
{
	char	**var;
	char	*temp;
	char	*new_entry;

	if (!envp || !key || !value)
		return (ft_putstr_fd("update_env_var: invalid arguments\n", 2), -1);
	var = find_env_var(key, envp);
	if (!var)
		return(create_env_var(key, value, &envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	free(temp);
	// free(*var); // doit travailler sur la copie alouée dynamiquement
	*var = new_entry;
	return (0);
}








// Function to update or create PWD and OLDPWD
void	actualize_cd_var(char *oldpwd, char *pwd, char ***envp)
{
	if (update_env_var("OLDPWD", oldpwd, *envp) == -1)
		ft_putstr_fd("cd: failed to create OLDPWD\n", 2);
	if (update_env_var("PWD", pwd, *envp) == -1)
		ft_putstr_fd("cd: failed to create PWD\n", 2);
}

// Function to go the actual dir
char	*find_actual_dir(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("cd: getcwd failed"), NULL);
	return (ft_strdup(pwd));
}

// Function to change directory to the parent directory
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
	if (!input || *input == '\0')
		input = ft_getenv("HOME", envp);
	if (!input)
		return (ft_putstr_fd("cd: HOME NOT SET", 2), NULL);
	if (!ft_strncmp(input, "..", 2) && ft_strlen(input) == 2)
		return (find_parent_dir());
	else if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
		return (find_actual_dir());
	else if (!ft_strncmp(input, "~", 1) && ft_strlen(input) == 1)
		return (ft_strdup("/"));
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
	actualize_cd_var(pwd, new_pwd, &envp);
	free(new_pwd);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 2)
		return (ft_printf("one arg needed"), 1);
	cd_cmd(av[1], envp);
	return (0);
}