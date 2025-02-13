/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_putendl_fd.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 17:02:53 by nifromon  #+##+# */
/*   Updated: 2024/11/07 17:12:13 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

//END
/*int	main(void)
{
	int	fd;

	fd = 1;
	printf("\nTest de ft_putendl_fd :\n\n");
	printf("Writing a bullshit string in the terminal + newline\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putendl_fd("Writing a bullshit string in the terminal + newline", fd);
	fd = open("testputendl", O_WRONLY | O_CREAT, 0777);
	ft_putendl_fd("Writing a bullshit string in a file + newline", fd);
	close(fd);
	return (0);
}*/
