/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:13:26 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 05:11:15 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TYPEDEF_H
# define FT_PRINTF_TYPEDEF_H

# include <stdarg.h>

// Enumerations
typedef enum e_ft_printf
{
	FT_PRINTF_C,
	FT_PRINTF_S,
	FT_PRINTF_P,
	FT_PRINTF_D,
	FT_PRINTF_I,
	FT_PRINTF_U,
	FT_PRINTF_X_LOW,
	FT_PRINTF_X_UPP,
	FT_PRINTF_PC
}	t_enum_ft_printf;

// Structures
typedef struct s_ft_printf
{
	int	hashtag;
	int	zero;
	int	hyphen;
	int	blank;
	int	plus;
	int	width;
	int	precision;
	int	specifier;
	int	printed;
}	t_ft_printf;

// Fonction alias
typedef void	(*t_dispatch)(t_ft_printf *format, va_list arg);

#endif