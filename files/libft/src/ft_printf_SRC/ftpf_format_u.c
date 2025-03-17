/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_u.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 21:18:43 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:20:06 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

static int	print_n_u_fd(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
		i += print_n_u_fd(n / LEN_BASE_10);
	ft_putchar_fd(n % LEN_BASE_10 + 48, FD);
	i++;
	return (i);
}

void	ftpf_format_u(t_ft_printf *format, va_list arg)
{
	unsigned int	n;

	n = va_arg(arg, unsigned int);
	format->printed += print_n_u_fd(n);
}

//END