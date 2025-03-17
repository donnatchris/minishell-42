/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 05:03:50 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 06:18:08 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//START
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./ft_printf_define.h"
# include "./ft_printf_typedef.h"
# include "../libft_H/libft.h"

// Fonctions
// Manager fonction
	// ft_printf.c
int			ft_printf(const char *format, ...);
// Employee Functions
	// init.c
int			ftpf_fetch_type(const char *format);
t_ft_printf	*ftpf_init_struct(void);
int			ftpf_fill_type(const char *s, t_ft_printf *format);
	// check.c
int			check_type(char c);
int			check_spec(const char *s);
	// ftpf_format_*.c
void		ftpf_format_c(t_ft_printf *format, va_list arg);
void		ftpf_format_s(t_ft_printf *format, va_list arg);
void		ftpf_format_p(t_ft_printf *format, va_list arg);
void		ftpf_format_d(t_ft_printf *format, va_list arg);
void		ftpf_format_i(t_ft_printf *format, va_list arg);
void		ftpf_format_u(t_ft_printf *format, va_list arg);
void		ftpf_format_x_low(t_ft_printf *format, va_list arg);
void		ftpf_format_x_upp(t_ft_printf *format, va_list arg);
void		ftpf_format_pc(t_ft_printf *percent, va_list arg);

# define UNDEFINE_FT_PRINTF_MACROS
# undef UNDEFINE_FT_PRINTF_MACROS

#endif

//END