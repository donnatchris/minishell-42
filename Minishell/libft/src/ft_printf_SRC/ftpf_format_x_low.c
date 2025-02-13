/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_x_low.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 21:57:16 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:20:23 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

static int	print_n_16_fd_low(unsigned int n)
{
	int	tmp;
	int	i;

	i = 0;
	if ((unsigned int)(LEN_BASE_16 - 1) < n)
		i += print_n_16_fd_low(n / LEN_BASE_16);
	tmp = BASE_16_LOW[(int)(n % LEN_BASE_16)];
	write(FD, &tmp, 1);
	i++;
	return (i);
}

void	ftpf_format_x_low(t_ft_printf *format, va_list arg)
{
	int	x_low;

	x_low = va_arg(arg, unsigned int);
	format->printed += print_n_16_fd_low(x_low);
}

//END