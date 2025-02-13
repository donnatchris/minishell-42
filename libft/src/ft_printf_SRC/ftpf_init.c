/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   init.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <nifromon@student.42perpignan.+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/15 23:00:21 by nifromon  #+##+# */
/*   Updated: 2024/11/15 23:24:52 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/ft_printf_H/ft_printf.h"

int	ftpf_fetch_type(const char *format)
{
	int	i;

	i = 0;
	if (format[i] == '%')
		i++;
	while (!(check_type(format[i])) && format[i])
		i++;
	if (format[i] == 'c')
		return (FT_PRINTF_C);
	else if (format[i] == 's')
		return (FT_PRINTF_S);
	else if (format[i] == 'd')
		return (FT_PRINTF_D);
	else if (format[i] == 'i')
		return (FT_PRINTF_I);
	else if (format[i] == 'u')
		return (FT_PRINTF_U);
	else if (format[i] == 'x')
		return (FT_PRINTF_X_LOW);
	else if (format[i] == 'X')
		return (FT_PRINTF_X_UPP);
	else if (format[i] == '%')
		return (FT_PRINTF_PC);
	return (FT_PRINTF_P);
}

t_ft_printf	*ftpf_init_struct(void)
{
	t_ft_printf	*format;

	format = (t_ft_printf *)malloc(sizeof(t_ft_printf));
	if (!format)
		return (NULL);
	format->hashtag = 0;
	format->zero = 0;
	format->hyphen = 0;
	format->blank = 0;
	format->plus = 0;
	format->width = 0;
	format->precision = 0;
	format->specifier = 0;
	format->printed = 0;
	return (format);
}

int	ftpf_fill_type(const char *s, t_ft_printf *format)
{
	if (!format)
		return (-1);
	format->specifier = ftpf_fetch_type(s);
	return (format->specifier);
}

//END