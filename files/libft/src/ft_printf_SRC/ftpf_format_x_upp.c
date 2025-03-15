/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_x_upp.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 22:03:37 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:20:32 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

static int	print_n_16_fd_upp(unsigned int n)
{
	int	tmp;
	int	i;

	i = 0;
	if ((unsigned int)(LEN_BASE_16 - 1) < n)
		i += print_n_16_fd_upp(n / LEN_BASE_16);
	tmp = BASE_16_UPP[(int)(n % LEN_BASE_16)];
	write(FD, &tmp, 1);
	i++;
	return (i);
}

void	ftpf_format_x_upp(t_ft_printf *format, va_list arg)
{
	int	x_upp;

	x_upp = va_arg(arg, unsigned int);
	format->printed += print_n_16_fd_upp(x_upp);
}

//END