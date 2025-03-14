/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_memcmp.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 18:48:42 by nifromon  #+##+# */
/*   Updated: 2024/11/12 11:22:54 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && tmp_s1[i] == tmp_s2[i])
		i++;
	if (i == n)
		return (0);
	return (tmp_s1[i] - tmp_s2[i]);
}

//END
/*int	main(void)
{
	printf("-----Str_1 = ABC | Str_2 = ABC-----\n\n");
	printf("expected result = 0\n");
	printf("result = %i", ft_memcmp("ABC", "ABC", 3));
	printf("\n\n-----Str_1 = ABC | Str_2 = ABCD-----\n\n");
printf("expected result = 0\n");
printf("result = %i", ft_memcmp("ABC", "ABCD", 3));
	printf("\n\n-----Str_1 = ABC | Str_2 = AB-----\n\n");
printf("expected result = 67\n");
printf("result = %i", ft_memcmp("ABC", "AB", 3));
	printf("\n\n-----Str_1 = ABA | Str_2 = ABZ-----\n\n");
printf("expected result = -25\n");
printf("result = %i", ft_memcmp("ABA", "ABZ", 3));
	printf("\n\n-----Str_1 = ABJ | Str_2 = ABC-----\n\n");
printf("expected result = 7\n");
printf("result = %i\n\n", ft_memcmp("ABJ", "ABC", 3));
	return (0);
}*/
