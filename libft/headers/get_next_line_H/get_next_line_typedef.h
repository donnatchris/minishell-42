/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_typedef.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:07:09 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 05:09:20 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_TYPEDEF_H
# define GET_NEXT_LINE_TYPEDEF_H

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}						t_gnl;

#endif