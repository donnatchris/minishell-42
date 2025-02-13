/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_bzero.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 13:13:51 by nifromon  #+##+# */
/*   Updated: 2024/11/06 13:09:20 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tmp_s;

	tmp_s = (char *) s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		tmp_s[i] = 0;
		i++;
	}
	return ;
}

//END
/*int	main(void)
{
	char	to_fill[20];

	printf("-----TEST-----\n\n");
	ft_bzero(to_fill, 20);
	printf("%s", to_fill);
	return (0);
}*/
