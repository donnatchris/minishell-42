/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_memchr.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 18:20:50 by nifromon  #+##+# */
/*   Updated: 2024/11/05 18:48:13 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	tmp_c;
	unsigned char	*tmp_s;

	i = 0;
	tmp_c = (unsigned char) c;
	tmp_s = (unsigned char *) s;
	while (i < n)
	{
		if (tmp_s[i] == tmp_c)
			return ((void *) tmp_s + i);
		i++;
	}
	return (NULL);
}

//END
/*int	main(void)
{
	char	string[] = "Is Charlie in the chocolate factory ?";

	printf("-----Initial String-----\n\n");
	printf("%s", string);
	printf("\n\n-----C in String till the end of String-----\n\n");
	printf("expected result = 'Charlie in the chocolate factory ?'\n");
	printf("result = %s", (char *) ft_memchr(string, 'C', 38));
	printf("\n\n-----C is in String at the 4 byte of String-----\n\n");
	printf("expected result = 'Charlie in the chocolate factory ?'\n");
printf("result = %s", (char *) ft_memchr(string, 'C', 4));
	printf("\n\n-----C not in String till the end of String-----\n\n");
	printf("expected result = '(null)'\n");
	printf("result = %s", (char *) ft_memchr(string, '!', 38));
	printf("\n\n-----C not in String till the 3 byte of String-----\n\n");
	printf("expected result = '(null)'\n");
printf("result = %s\n\n", (char *) ft_memchr(string, 'C', 3));
	return (0);
}*/
