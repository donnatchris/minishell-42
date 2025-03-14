/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_putnbr_fd.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 17:15:10 by nifromon  #+##+# */
/*   Updated: 2024/11/07 17:42:20 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 0 && nbr <= 9)
		ft_putchar_fd((char)(nbr + 48), fd);
	else
	{
		ft_putnbr_fd((int)(nbr / 10), fd);
		ft_putnbr_fd((int)(nbr % 10), fd);
	}
}

//END
/*int	main(void)
{
	int	fd;

	fd = 1;
	printf("\nTest de ft_putbr_fd :\n\n");
	printf("0\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putnbr_fd(0, fd);
	printf("\n\n");
	printf("42\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putnbr_fd(42, fd);
	printf("\n\n");
	printf("-42\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putnbr_fd(-42, fd);
	printf("\n\n");
	printf("2147483647\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putnbr_fd(2147483647, fd);
	printf("\n\n");
	printf("-2147483648\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putnbr_fd(-2147483648, fd);
	printf("\n\n");
	fd = open("testputnbr", O_WRONLY | O_CREAT, 0777);
	ft_putnbr_fd(42, fd);
	close(fd);
	return (0);
}*/
