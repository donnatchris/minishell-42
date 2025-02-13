/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strrchr.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/05 17:40:47 by nifromon  #+##+# */
/*   Updated: 2024/11/05 17:57:18 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	tmp_c;
	char	*checkpoint;

	i = 0;
	checkpoint = NULL;
	tmp_c = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == tmp_c)
			checkpoint = (char *) &(s[i]);
		i++;
	}
	if (s[i] == tmp_c)
		checkpoint = (char *) &(s[i]);
	return (checkpoint);
}

//END
/*int	main(void)
{
	char	string[] = "Is Charlie in the chocolate factory ? Charlie is here";

	printf("-----Initial String-----\n\n");
	printf("%s", string);
	printf("\n\n-----Last of Occurence of C in String-----\n\n");
	printf("%s", ft_strrchr(string, 'C'));
	printf("\n\n-----C is equal to NULL-----\n\n");
	printf("%s", ft_strrchr(string, '\0'));
	printf("\n\n-----C is not in String-----\n\n");
	printf("%s\n\n", ft_strrchr(string, '!'));
	return (0);
}*/
