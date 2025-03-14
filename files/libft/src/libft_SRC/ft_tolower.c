/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_tolower.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 17:11:56 by nifromon  #+##+# */
/*   Updated: 2024/11/05 17:16:23 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	return (c);
}

//END
/*int	main(void)
{
	printf("-----Uppercase-----\n\n");
	printf("A -> %c", ft_tolower('A'));
	printf("\n\n-----Lowercase-----\n\n");
	printf("a -> %c", ft_tolower('a'));
	printf("\n\n-----! Alpha-----\n\n");
	printf("0 -> %c\n\n", ft_tolower('0'));
	return (0);
}*/
