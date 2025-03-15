/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strtrim.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 13:51:16 by nifromon  #+##+# */
/*   Updated: 2024/11/06 14:26:06 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

static size_t	to_trim(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*trimed(const char *s1, size_t start, size_t len)
{
	char	*trim;
	size_t	i;

	i = 0;
	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	trim = ft_calloc(len + 1, sizeof(char));
	if (!trim)
		return (NULL);
	while (i < len)
	{
		trim[i] = s1[start + i];
		i++;
	}
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (to_trim(set, s1[i]))
		i++;
	while (to_trim(set, s1[j]))
		j--;
	return (trimed(s1, i, j - (i - 1)));
}

//END
/*int	main(void)
{
	printf("\nTest de ft_strtrim :\n\n");
	printf("'bonjour' : '%s'\n", ft_strtrim("bonjour", " "));
	printf("'bonjour' : '%s'\n", ft_strtrim(" bonjour ", " "));
	printf("'onjour' : '%s'\n", ft_strtrim(" bonjour ", " b"));
	printf("'bonjour' : '%s'\n", ft_strtrim(" bonjour", " "));
	printf("'bonjour' : '%s'\n", ft_strtrim("bonjour ", " "));
	printf("'onjou' : '%s'\n", ft_strtrim("bonjour ", "br "));
	printf("'' : '%s'\n", ft_strtrim("", " "));
	printf("'test' : '%s'\n", ft_strtrim("test", ""));
	printf("'te st' : '%s'\n", ft_strtrim(" te st ", " "));
	printf("'' : '%s'\n\n", ft_strtrim(" b  ", "b "));
	return (0);
}*/
