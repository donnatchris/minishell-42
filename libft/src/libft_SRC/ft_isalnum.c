/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_isalnum.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 15:10:11 by nifromon  #+##+# */
/*   Updated: 2024/11/05 13:12:38 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

//END
/*int	main(void)
{
	int	i;

	i = '0';
	write(1, "--------DIGIT--------\n", 22);
	while (i < ':')
	{
		if (ft_isalnum(i) == 1)
			write(1, "ALNUM\n", 6);
		else
			write(1, "NOT ALNUM\n", 10);
		i++;
	}
	i = 'A';
	write(1, "-----ALPHA_UPPER-----\n", 22);
	while (i < '[')
	{
		if (ft_isalnum(i) == 1)
			write(1, "ALNUM\n", 6);
		else
			write(1, "NOT ALNUM\n", 10);
		i++;
	}
	i = 'a';
	write(1, "-----ALPHA_LOWER-----\n", 22);
	while (i < '{')
	{
		if (ft_isalnum(i) == 1)
			write(1, "ALNUM\n", 6);
		else
			write(1, "NOT ALNUM\n", 10);
		i++;
	}
	return (0);
}*/
