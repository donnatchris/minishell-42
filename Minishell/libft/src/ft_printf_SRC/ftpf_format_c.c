/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_c.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 18:23:29 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:18:55 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

static int	print_c_fd(char c)
{
	return (write(FD, &c, 1));
}

void	ftpf_format_c(t_ft_printf *format, va_list arg)
{
	int	c;

	c = va_arg(arg, int);
	format->printed += print_c_fd(c);
}

//END