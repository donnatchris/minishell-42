/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strdup.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 10:55:10 by nifromon  #+##+# */
/*   Updated: 2024/11/12 11:29:23 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

//END
/*int	main(void)
{
	char	*ptr;

	printf("\nTest de ft_strdup :\n");
	ptr = ft_strdup("string");
	printf("'string' : %s\n", ptr);
	free(ptr);
	ptr = ft_strdup(NULL);
	printf("(null) : %s\n\n", ptr);
	free(ptr);
	return (0);
}*/
