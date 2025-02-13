/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:40:00 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 06:09:44 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//START
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "./get_next_line_typedef.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Manager fonction
	// get_next_line.c
char		*get_next_line(int fd);
// Employee fonction
	// get_next_line_utils.c
void		gnl_stock_replenishment(t_gnl **store, char *product, int fd);
int			gnl_inventory(t_gnl **store, int fd);
char		*gnl_fetch_queue(t_gnl *store);
void		gnl_cutting_in(t_gnl **store);
	// get_next_line_utils.c
int			gnl_search_newline(t_gnl *store);
t_gnl		*gnl_ft_lstlast(t_gnl *store);
void		gnl_cpylst_to_str(t_gnl *store, char *queue);
int			gnl_lstlen_till_newline(t_gnl *store);
void		gnl_free_store(t_gnl **store, t_gnl *clean, char *product);

#endif

//END
