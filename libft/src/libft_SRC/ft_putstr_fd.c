/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_putstr_fd.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 16:50:00 by nifromon  #+##+# */
/*   Updated: 2024/11/07 17:01:14 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

//END
/*int	main(void)
{
	int	fd;

	fd = 1;
	printf("\nTest de ft_putstr_fd :\n\n");
	printf("Writing a bullshit string in the terminal\n\n");
	printf("|\n");
	printf("to\n");
	printf("|\n\n");
	ft_putstr_fd("Writing a bullshit string in the terminal", fd);
	printf("\n\n");
	fd = open("testputstr", O_WRONLY | O_CREAT, 0777);
	ft_putstr_fd("Writing a bullshit string in a file", fd);
	close(fd);
	return (0);
}*/
