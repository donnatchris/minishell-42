/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   print_format_p.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 19:49:57 by nifromon  #+##+# */
/*   Updated: 2024/11/15 22:19:45 by nifromon ###   ########.fr   */
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

static int	print_n_16_fd(unsigned long long n)
{
	int	tmp;
	int	i;

	i = 0;
	if ((unsigned long long)(LEN_BASE_16 - 1) < n)
		i += print_n_16_fd(n / LEN_BASE_16);
	tmp = BASE_16_LOW[(int)(n % LEN_BASE_16)];
	write(FD, &tmp, 1);
	i++;
	return (i);
}

static int	print_p_fd(unsigned long long p)
{
	ft_putstr_fd(OX, FD);
	return (print_n_16_fd(p) + LEN_OX);
}

void	ftpf_format_p(t_ft_printf *format, va_list arg)
{
	unsigned long long	p;

	p = va_arg(arg, unsigned long long);
	if (!p)
	{
		format->printed += print_s_fd(NULL_P);
		return ;
	}
	format->printed += print_p_fd(p);
}

//END