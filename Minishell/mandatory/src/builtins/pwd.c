#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void	pwd_cmd()
{
	char	current_dir[PATH_MAX];

	if (!getcwd(current_dir, sizeof(current_dir))
		perror("pwd: error retrieving current directory");
	else
	// 	ft_printf("%s\n", current_dir);
		printf("%s\n", current_dir);
}

// int	main(void)
// {
// 	pwd_cmd();
// 	return (0);
// }