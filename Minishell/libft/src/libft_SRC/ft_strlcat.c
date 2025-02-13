/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strlcat.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 15:31:40 by nifromon  #+##+# */
/*   Updated: 2024/11/12 10:45:28 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dst)
		return (size + len_src);
	if (len_src < size - len_dst)
		ft_memcpy(dst + len_dst, src, len_src + 1);
	else
	{
		ft_memcpy(dst + len_dst, src, (size - len_dst - 1));
		dst[size - 1] = '\0';
	}
	return (len_dst + len_src);
}

//END
/*int	main(void)
{
	charsource[] = "I'm me";
chardest[] = "Hello World ! ";

printf("-----Source | size = 6-----\n\n");
printf("%s", source);
	printf("\n\n-----Dest | size = 14-----\n\n");
	printf("%s", dest);
	printf("\n\n-----Len_source + Len_dest = 20-----\n\n");
	printf("%zu", ft_strlcat(dest, source, 21));
printf("\n\n-----Cat | size = 20-----\n\n");
printf("%s\n\n", dest);
return (0);
}*/
