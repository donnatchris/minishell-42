#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_echo -Wall -Werror -Wextra echo.c  -L ../../../libft -lft_inc -I../../../libft/headers/libft_H
*****************************************************************************/

void	echo_cmd(char **array)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	if (ft_strncmp(array[0], "-n", 2) == 0)
	{
		newline = 1;
		i++;
	}
	while (array[i] != NULL)
	{
		ft_putstr_fd(array[i], 1);
		if (array[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
	return ;
}

/*int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 2)
		return (write(1, "\n", 1), 0);
	while (argv[i] != NULL)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	echo_cmd(argv);
	return (0);
}*/