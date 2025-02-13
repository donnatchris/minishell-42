/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   check.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 22:17:38 by nifromon  #+##+# */
/*   Updated: 2024/11/15 23:07:27 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

int	check_type(char c)
{
	if (!c)
		return (0);
	if (c == 'i' || c == 'd' || c == 'u' || c == 's' || c == 'c'
		|| c == 'x' || c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}

int	check_spec(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '%')
		i++;
	while (s[i])
	{
		if (check_type(s[i]))
			return (1);
		i++;
	}
	return (0);
}

//END
