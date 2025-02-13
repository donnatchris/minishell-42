/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strncmp.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 17:58:23 by nifromon  #+##+# */
/*   Updated: 2024/11/12 11:41:28 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && *(unsigned char *)s1 == *(unsigned char *)s2
		&& n-- > 0)
	{
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//END
/*int	main(void)
{
	printf("-----Str_1 = ABC | Str_2 = ABC-----\n\n");
	printf("expected result = 0\n");
	printf("result = %i", ft_strncmp("ABC", "ABC", 3));
	printf("\n\n-----Str_1 = ABC | Str_2 = ABCD-----\n\n");
	printf("expected result = 0\n");
	printf("result = %i", ft_strncmp("ABC", "ABCD", 3));
	printf("\n\n-----Str_1 = ABC | Str_2 = AB-----\n\n");
	printf("expected result = 67\n");
	printf("result = %i", ft_strncmp("ABC", "AB", 3));
	printf("\n\n-----Str_1 = ABA | Str_2 = ABZ-----\n\n");
	printf("expected result = -25\n");
	printf("result = %i", ft_strncmp("ABA", "ABZ", 3));
	printf("\n\n-----Str_1 = ABJ | Str_2 = ABC-----\n\n");
	printf("expected result = 7\n");
	printf("result = %i\n\n", ft_strncmp("ABJ", "ABC", 3));
	return (0);
}*/
