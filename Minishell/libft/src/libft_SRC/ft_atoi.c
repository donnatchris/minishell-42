/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_atoi.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 08:21:30 by nifromon  #+##+# */
/*   Updated: 2024/11/06 10:54:53 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

static int	is_white_space(int c)
{
	if ((c > 8 && c < 14) || (c == 32))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	res;
	size_t	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (is_white_space(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+' && nptr[i + 1] != '-')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((nptr[i] != '\0') && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

//END
/*int	main(void)
{
	printf("\nTest de ft_atoi :\n\n");
	printf("0 : %d\n", ft_atoi("0"));
	printf("1 : %d\n", ft_atoi("1"));
	printf("10 : %d\n", ft_atoi("10"));
	printf("596 : %d\n", ft_atoi("596"));
	printf("-83 : %d\n", ft_atoi("-83"));
	printf("-2147483648 : %d\n", ft_atoi("-2147483648"));
	printf("0 : %d\n", ft_atoi("---48"));
	printf("0 : %d\n", ft_atoi("-+596"));
	printf("3 : %d\n\n", ft_atoi(" \t +3"));
	return (0);
}*/
