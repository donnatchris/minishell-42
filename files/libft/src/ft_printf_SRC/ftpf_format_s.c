/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_s.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 19:42:25 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:19:55 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

static int	print_s_fd(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], FD);
		i++;
	}
	return (i);
}

void	ftpf_format_s(t_ft_printf *format, va_list arg)
{
	char	*s;

	s = va_arg(arg, char *);
	if (!s)
	{
		format->printed += print_s_fd(NULL_S);
		return ;
	}
	format->printed += print_s_fd(s);
}

//END