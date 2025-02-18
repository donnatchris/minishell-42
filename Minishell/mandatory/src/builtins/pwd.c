#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_pwd -Wall -Werror -Wextra pwd.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

// Function to print the actual working directory
// like the pwd comand
void	pwd_cmd()
{
	char	current_dir[PATH_MAX];

	if (!getcwd(current_dir, sizeof(current_dir)))
		perror("pwd: error retrieving current directory");
	else
		ft_printf("%s\n", current_dir);
}

// int	main(void)
// {
// 	pwd_cmd();
// 	return (0);
// }