/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_memmove.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 13:53:49 by nifromon  #+##+# */
/*   Updated: 2024/11/12 10:46:30 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*tmp_dst;
	char	*tmp_src;

	if (!dest && !src)
		return (NULL);
	tmp_dst = (char *) dest;
	tmp_src = (char *) src;
	i = 0;
	if (tmp_dst > tmp_src)
	{
		while (n-- > 0)
			tmp_dst[n] = tmp_src[n];
	}
	else
	{
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
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

int main(void)
{
charinit_mem[20];
chardest_mem[20];

ft_memset(init_mem, 'A', 20);
ft_memset(dest_mem, 'B', 20);
printf("-----Init_mem-----\n\n");
printf("%s", init_mem);
printf("\n\n-----Dest_mem-----\n\n");
printf("%s", dest_mem);
ft_memmove(dest_mem, init_mem, 0);
printf("\n\n-----Memmove | n = 0-----\n\n");
printf("%s", dest_mem);
ft_memmove(dest_mem, init_mem, 10);
printf("\n\n-----Memmove | n = 10-----\n\n");
printf("%s", dest_mem);
ft_memmove(dest_mem, init_mem, 20);
printf("\n\n-----Memmove | n = 20-----\n\n");
printf("%s\n", dest_mem);
return (0);
}*/
