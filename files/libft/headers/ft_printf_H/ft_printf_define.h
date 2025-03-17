/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:17:26 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 06:17:16 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DEFINE_H
# define FT_PRINTF_DEFINE_H

# define FD				1
# define NULL_S			"(null)"
# define OX				"0x"
# define LEN_OX 		2
# define NULL_P			"(nil)"
# define BASE_10		"012345678910"
# define LEN_BASE_10	10
# define BASE_16_LOW	"0123456789abcdef"
# define BASE_16_UPP	"0123456789ABCDEF"
# define NULL_HEX		"(nil)"
# define LEN_BASE_16	16
# define INT_MIN_S		"-2147483648"

# ifdef UNDEFINE_FT_PRINTF_MACROS
#  undef FD
#  undef NULL_S
#  undef OX
#  undef LEN_OX
#  undef NULL_P
#  undef BASE_10
#  undef LEN_BASE_10
#  undef BASE_16_LOW
#  undef BASE_16_UPP
#  undef NULL_HEX
#  undef LEN_BASE_16
#  undef INT_MIN_S
# endif

#endif