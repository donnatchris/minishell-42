/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_isprint.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 16:06:35 by nifromon  #+##+# */
/*   Updated: 2024/11/04 16:25:52 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

//END
/*int	main(void)
{
	int	i;

	i = ' ';
	while (i < 127)
	{
		if (ft_isprint(i) == 1)
			write(1, "PRINTABLE\n", 10);
		else
			write(1, "NOT PRINTABLE\n", 14);
		i++;
	}
	return (0);
}*/
