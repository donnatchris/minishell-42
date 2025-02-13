/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strlcpy.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 14:27:21 by nifromon  #+##+# */
/*   Updated: 2024/11/05 15:30:27 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}

//END
/*int	main(void)
{
	char	source[] = "Hello World !";
	char	dest[6];

	printf("-----Source-----\n\n");
	printf("%s", source);
	ft_strlcpy(dest, source, 6);
	printf("\n\n------Dest------\n\n");
	printf("%s", dest);
	printf("\n\n---Len_source---\n\n");
	printf("%zu\n", ft_strlcpy(dest, source, 5));
	return (0);
}*/
