/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_isascii.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 15:56:37 by nifromon  #+##+# */
/*   Updated: 2024/11/04 16:05:39 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

//END
/*int	main(void)
{
	int	i;

	i = '\0';
	while (i <= 127)
	{
		if (ft_isascii(i) == 1)
			write(1, "ASCII\n", 6);
		else
			write(1, "NOT ASCII\n", 10);
		i++;
	}
	return (0);
}*/
