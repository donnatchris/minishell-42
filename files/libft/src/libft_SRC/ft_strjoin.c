/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strjoin.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 13:27:49 by nifromon  #+##+# */
/*   Updated: 2024/11/06 13:49:22 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*joined;

	i = 0;
	j = 0;
	joined = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!joined)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined[j++] = s2[i++];
	}
	joined[j] = '\0';
	return (joined);
}

//END
/*int	main(void)
{
	printf("\nTest de ft_strjoin :\n\n");
	printf("abcdef : %s\n",	ft_strjoin("abc", "def"));
	printf("abc : %s\n", ft_strjoin("", "abc"));
	printf("abc : %s\n", ft_strjoin("abc", ""));
	printf("'' : '%s'\n\n", ft_strjoin("", ""));
	return (0);
}*/
