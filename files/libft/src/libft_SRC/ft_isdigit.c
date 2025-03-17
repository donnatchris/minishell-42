/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_isdigit.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 14:00:06 by nifromon  #+##+# */
/*   Updated: 2024/11/04 15:08:26 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

//END
/*int	main(void)
{
	int	i;

	i = '0';
	while (i < ':')
	{
		if (ft_isdigit(i) == 1)
			write(1, "DIGIT\n", 6);
		else
			write(1, "NOT DIGIT\n", 10);
		i++;
	}
	return (0);
}*/
