/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_memcpy.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 13:27:05 by nifromon  #+##+# */
/*   Updated: 2024/11/05 13:53:23 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dest == NULL && src == NULL)
		return (dest);
	tmp_dst = (unsigned char *) dest;
	tmp_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dest);
}

//END
/*void*ft_memset(void *s, int c, size_t n)
{
size_t  i;
unsigned char   *tmp_s;

tmp_s = (unsigned char *) s;
i = 0;
while (i < n)
{
tmp_s[i] = (unsigned char) c;
i++;
}
return (s);
}

int	main(void)
{
	char	init_mem[20];
	char	dest_mem[20];

	ft_memset(init_mem, 'A', 20);
	ft_memset(dest_mem, 'B', 20);
	printf("-----Init_mem-----\n\n");
	printf("%s", init_mem);
	printf("\n\n-----Dest_mem-----\n\n");
	printf("%s", dest_mem);
	ft_memcpy(dest_mem, init_mem, 0);
	printf("\n\n-----Memcpy | n = 0-----\n\n");
	printf("%s", dest_mem);
	ft_memcpy(dest_mem, init_mem, 10);
	printf("\n\n-----Memcpy | n = 10-----\n\n");
	printf("%s", dest_mem);
	ft_memcpy(dest_mem, init_mem, 20);
	printf("\n\n-----Memcpy | n = 20-----\n\n");
	printf("%s\n", dest_mem);
	return (0);
}*/
