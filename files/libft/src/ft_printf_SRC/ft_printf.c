/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_printf.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 23:26:40 by nifromon  #+##+# */
/*   Updated: 2024/11/15 23:57:05 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

void	ftpf_format_pc(t_ft_printf *percent, va_list arg)
{
	(void) arg;
	ft_putchar_fd('%', FD);
	percent->printed += 1;
}

static int	ft_percent_len(const char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (check_type(s[i]))
			return (i);
		i++;
	}
	return (0);
}

static void	dispatching(int type, t_ft_printf *format, va_list arg)
{
	t_dispatch	arr[9];

	arr[FT_PRINTF_C] = &ftpf_format_c;
	arr[FT_PRINTF_S] = &ftpf_format_s;
	arr[FT_PRINTF_P] = &ftpf_format_p;
	arr[FT_PRINTF_D] = &ftpf_format_d;
	arr[FT_PRINTF_I] = &ftpf_format_i;
	arr[FT_PRINTF_U] = &ftpf_format_u;
	arr[FT_PRINTF_X_LOW] = &ftpf_format_x_low;
	arr[FT_PRINTF_X_UPP] = &ftpf_format_x_upp;
	arr[FT_PRINTF_PC] = &ftpf_format_pc;
	arr[type](format, arg);
}

static int	parsing(const char *format, va_list arg)
{
	t_ft_printf	*type;
	int			printed;
	int			specifier;

	type = ftpf_init_struct();
	if (format && type)
	{
		specifier = ftpf_fetch_type(format);
		type->specifier = specifier;
	}
	dispatching(type->specifier, type, arg);
	printed = type->printed;
	free(type);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		printed;
	int		i;

	printed = 0;
	i = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(check_spec(&format[i])))
				return (0);
			printed += parsing(&format[i], arg);
			i += ft_percent_len(&format[i]);
		}
		else
		{
			ft_putchar_fd(format[i], FD);
			printed++;
		}
		i++;
	}
	va_end(arg);
	return (printed);
}

//END