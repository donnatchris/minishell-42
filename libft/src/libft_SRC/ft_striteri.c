/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_striteri.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/07 15:32:15 by nifromon  #+##+# */
/*   Updated: 2024/11/07 16:07:15 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

//END