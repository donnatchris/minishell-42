#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_env_value(const char *key, const char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp)
	}
}

int	cd_cmd(const char *path, const char **envp)
{
	char	old_pwd[PATH_MAX];
	char	cwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		perror("cd error: getcwd failed");
	if (!path || *path == '\0')
	{

	}


	if (chdir(path) == -1)
		return (perror("cd error"), -1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 2)
		perror("one arg nedded");
	else
		cd_cmd(av[1], envp);
	return (0);
}