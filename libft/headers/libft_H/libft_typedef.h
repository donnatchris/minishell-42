/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_typedef.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:19:18 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 05:10:35 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TYPEDEF_H
# define LIBFT_TYPEDEF_H

typedef struct s_libft
{
	void			*content;
	struct s_libft	*next;
}						t_libft;

#endif