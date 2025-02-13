/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strmapi.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 14:33:51 by nifromon  #+##+# */
/*   Updated: 2024/11/07 16:12:32 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapi;

	i = 0;
	mapi = (char *)malloc((ft_strlen(s) + 1) * sizeof (char));
	if (!mapi)
		return (NULL);
	while (i < ft_strlen(s))
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}

//END
/*char	ft_test_mapi(unsigned int i, char c)
{
	i = 0;
	return (c - 32);
}

int	main(void)
{
	printf("\nTest de ft_strmapi :\n\n");
	printf("ABC : %s\n\n", ft_strmapi("abc", ft_test_mapi));
	return (0);
}*/
