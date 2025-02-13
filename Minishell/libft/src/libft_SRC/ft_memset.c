/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_memset.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 10:20:30 by nifromon  #+##+# */
/*   Updated: 2024/11/05 13:13:07 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s;

	tmp_s = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		tmp_s[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

//END
/*int	main(void)
{
	char	to_fill[20];

	printf("-----TEST_1-----\n");
	ft_memset(to_fill, '-', sizeof (to_fill));
	printf("\n%s\n\n", to_fill);
	printf("-----TEST_2-----\n");
	ft_memset(to_fill, 'A', 10);
	printf("\n%s\n\n", to_fill);
	printf("-----TEST_3-----\n");
	ft_memset(to_fill, 33, 10);
	printf("\n%s\n\n", to_fill);
	printf("-----TEST 4-----\n");
	ft_memset(to_fill, ' ', 10);
	printf("\n%s\n\n", to_fill);
	return (0);
}*/
