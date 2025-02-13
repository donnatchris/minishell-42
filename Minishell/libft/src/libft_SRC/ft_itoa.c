/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_itoa.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 10:32:05 by nifromon  #+##+# */
/*   Updated: 2024/11/12 13:29:25 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

static size_t	int_len(long nbr)
{
	size_t	i;

	i = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	long	nbr;
	char	*result;

	nbr = n;
	i = int_len(nbr) - 1;
	result = (char *)ft_calloc(int_len(nbr) + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (nbr == 0)
		return (result[0] = '0', result);
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	while (nbr > 0)
	{
		result[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i--;
	}
	return (result);
}

//END
/*int	main(void)
{
	printf("\nTest de ft_itoa :\n\n");
	printf("0 : %s\n", ft_itoa(0));
	printf("1 : %s\n", ft_itoa(1));
	printf("-1 : %s\n", ft_itoa(-1));
	printf("234 : %s\n", ft_itoa(234));
	printf("-5689 : %s\n", ft_itoa(-5689));
	printf("2147483647 : %s\n", ft_itoa(2147483647));
	printf("-2147483648 : %s\n\n", ft_itoa(-2147483648));
	return (0);
}*/
