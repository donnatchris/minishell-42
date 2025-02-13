/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strchr.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 17:17:03 by nifromon  #+##+# */
/*   Updated: 2024/11/05 18:27:39 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	tmp_c;

	i = 0;
	tmp_c = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == tmp_c)
			return ((char *) &(s[i]));
		i++;
	}
	if (s[i] == tmp_c)
		return ((char *) &(s[i]));
	return (NULL);
}

//END
/*int	main(void)
{
	char	string[] = "Is Charlie in the chocolate factory ?";

	printf("-----Initial String-----\n\n");
	printf("%s", string);
	printf("\n\n-----C in String-----\n\n");
	printf("%s", ft_strchr(string, 'C'));
	printf("\n\n-----C is equal to NULL-----\n\n");
	printf("%s", ft_strchr(string, '\0'));
	printf("\n\n-----C is not in String-----\n\n");
	printf("%s\n\n", ft_strchr(string, '!'));
	return (0);
}*/
