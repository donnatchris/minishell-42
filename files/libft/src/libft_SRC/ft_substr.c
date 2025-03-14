/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_substr.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 12:58:31 by nifromon  #+##+# */
/*   Updated: 2024/11/06 13:46:42 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp_s;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	tmp_s = ft_calloc(len + 1, sizeof(char));
	if (!tmp_s)
		return (NULL);
	while (i < len)
	{
		tmp_s[i] = s[start + i];
		i++;
	}
	return (tmp_s);
}

//END
/*int	main(void)
{
	char	stest[100] = "test";

	printf("\nTest de ft_substr :\n\n");
	printf("njo : %s\n", ft_substr("bonjour", 2, 3));
	printf("njour : %s\n", ft_substr("bonjour", 2, 5));
	printf("njour : %s\n", ft_substr("bonjour", 2, 6));
	printf("r : %s\n", ft_substr("bonjour", 6, 1));
	printf("'' : '%s'\n", ft_substr("bonjour", 6, 0));
	ft_memset(stest + 6, 'a', 50);
	printf("'' : '%s'\n\n", ft_substr(stest, 10, 1));
	return (0);
}*/
