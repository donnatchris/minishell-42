/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_putchar_fd.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 16:08:34 by nifromon  #+##+# */
/*   Updated: 2024/11/07 16:47:53 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

//END
/*int	main(void)
{
	int	fd;

	fd = 1;
	printf("\nTest de ft_putchar_fd :\n\n");
	printf("a\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putchar_fd('a', fd);
	printf("\n\n");
	fd = open("testputchar", O_WRONLY | O_CREAT, 0777);
	ft_putchar_fd('b', fd);
	close(fd);
	return (0);
}*/
