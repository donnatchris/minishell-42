/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strnstr.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 19:03:58 by nifromon  #+##+# */
/*   Updated: 2024/11/06 14:34:21 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] != '\0'
			&& i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *) big + i);
		i++;
	}
	return (0);
}

//END
/*int	main(void)
{
	char	string[] = "Where is Charlie in the string ?";
	char	to_find[] = "Charlie";
	char	empty_to_find[] = "\0";

	printf("-----Initial string-----\n\n");
	printf("%s", string);
	printf("\n\n-----String to find in the Initial string-----\n\n");
	printf("%s", to_find);
	printf("\n\n-----Results with a empty string to find-----\n\n");
	printf("expected result : 'Where is Charlie in the string ?'\n");
	printf("result : %s", ft_strnstr(string, empty_to_find, 32));
	printf("\n\n-----Results till end of the Initial string-----\n\n");
	printf("expected result : 'Charlie in the string ?'\n");
	printf("result : %s", ft_strnstr(string, to_find, 32));
	printf("\n\n-----Results at 16 bytes of the Initial string-----\n\n");
	printf("expected result : 'Charlie in the string ?'\n");
	printf("result : %s", ft_strnstr(string, to_find, 16));
	printf("\n\n-----Results at 12 bytes of the Initial string-----\n\n");
	printf("expected result : '(null)'\n");
	printf("result : %s\n\n", ft_strnstr(string, to_find, 12));
	return (0);
}*/
