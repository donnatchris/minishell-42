/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_toupper.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 16:58:18 by nifromon  #+##+# */
/*   Updated: 2024/11/05 17:11:40 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}

//END
/*int	main(void)
{
	printf("-----Lowercase-----\n\n");
	printf("a -> %c", ft_toupper('a'));
	printf("\n\n-----Uppercase-----\n\n");
	printf("A -> %c", ft_toupper('A'));
	printf("\n\n-----! Alpha-----\n\n");
	printf("0 -> %c\n\n", ft_toupper('0'));
	return (0);
}*/
