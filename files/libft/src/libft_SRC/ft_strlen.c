/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strlen.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 16:31:43 by nifromon  #+##+# */
/*   Updated: 2024/11/04 16:52:27 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//END
/*int	main(void)
{
	printf("%i\n", ft_strlen("There is 32 bytes in this string"));
	return (0);
}*/
