/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_calloc.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 09:10:35 by nifromon  #+##+# */
/*   Updated: 2024/11/07 10:31:42 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*tmp_s;

	i = 0;
	tmp_s = (unsigned char *)malloc(nmemb * size);
	if (!tmp_s)
		return (NULL);
	while (i < nmemb * size)
	{
		tmp_s[i] = 0;
		i++;
	}
	return (tmp_s);
}

//END
/*int	main(void)
{
	char	*ptr;
	size_t	i;

	printf("\nTest de ft_calloc;\n\n");
	ptr = ft_calloc(5, sizeof(int));
	printf("00000 : ");
	i = 0;
	while (i < 5)
	{
		printf("%i", (int) ptr[i]);
		i++;
	}
	printf("\n");
	free(ptr);
	ptr = ft_calloc(10, sizeof(int));
	printf("0000000000 : ");
	i = 0;
	while (i < 10)
	{
		printf("%i", (int) ptr[i]);
		i++;
	}
	printf("\n");
	free(ptr);
	ptr = ft_calloc(1000000000000000000, sizeof(int));
	printf("(null) : %s\n\n", ptr);
	free(ptr);
	return (0);
}*/
