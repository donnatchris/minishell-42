/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_isalpha.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 13:23:02 by nifromon  #+##+# */
/*   Updated: 2024/11/04 15:49:49 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

//END
/*int	main(void)
{
	int	i;

	i = 'A';
	write(1, "-----ALPHA_UPPER-----\n", 22);
	while (i < '[')
	{
		if (ft_isalpha(i) == 1)
			write(1, "ALPHA\n", 6);
		else
			write(1, "NOT ALPHA\n", 10);
		i++;
	}
	i = 'a';
	write(1, "-----ALPHA_LOWER-----\n", 22);
	while (i < '{')
	{
		if (ft_isalpha(i) == 1)
			write(1, "ALPHA\n", 6);
		else
			write(1, "NOT ALPHA\n", 10);
		i++;
	}
	return (0);
}*/
