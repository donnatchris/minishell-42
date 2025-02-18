#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_cd -Wall -Werror -Wextra cd.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

// Function to change directory to the parent directory
int	go_to_parent_dir(void)
{
	char	pwd[PATH_MAX];
	char	*ptr;

	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("cd: getcwd failed"), -1);
	ptr = ft_strrchr(pwd, '/');
	if (ptr == NULL)
		return (perror("cd: invalid path"), -1);
	if (ptr == pwd)
	{
		if (chdir("/") == -1)
			return (perror("cd error"), -1);
	}
	else
	{
		*ptr = '\0';
		if (chdir(pwd) == -1)
			return (perror("cd error"), -1);
	}
	return (0);
}

// Function to change directory
// like the cd command
int	cd_cmd(const char *path)
{
	if (!path || *path == '\0')
		path = getenv("HOME");
	if (!path)
		return (ft_printf("cd: HOME NOT SET "), -1);
	if (!ft_strncmp(path, "..", 2) && ft_strlen(path) == 2)
		return (go_to_parent_dir());
	else if (!ft_strncmp(path, ".", 1) && ft_strlen(path) == 1)
		return (0);
	else if (!ft_strncmp(path, "~", 1) && ft_strlen(path) == 1)
	{
		if (chdir("/") == -1)
			return (perror("cd error"), -1);
		return (0);
	}
	if (chdir(path) == -1)
		return (perror("cd error"), -1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_printf("one arg needed"), 1);
	cd_cmd(av[1]);
	return (0);
}