/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:41:34 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 06:04:20 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//START
#include "../../headers/get_next_line_H/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	*store[200000];
	t_gnl			*error;
	char			*queue;

	if (fd < 0 || fd > 200000 || BUFFER_SIZE <= 0)
		return (NULL);
	queue = NULL;
	if (gnl_inventory(store, fd) == -1)
	{
		while (store[fd])
		{
			error = store[fd]->next;
			free(store[fd]->content);
			free(store[fd]);
			store[fd] = error;
		}
		store[fd] = NULL;
	}
	if (!store[fd])
		return (NULL);
	queue = gnl_fetch_queue(store[fd]);
	gnl_cutting_in(&store[fd]);
	return (queue);
}

int	gnl_inventory(t_gnl **store, int fd)
{
	int		bill;
	char	*product;

	bill = 0;
	while (!gnl_search_newline(store[fd]))
	{
		product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!product)
			return (bill);
		bill = read(fd, product, BUFFER_SIZE);
		if (bill <= 0)
		{
			free(product);
			product = NULL;
			return (bill);
		}
		product[bill] = '\0';
		gnl_stock_replenishment(store, product, fd);
	}
	return (bill);
}

void	gnl_stock_replenishment(t_gnl **store, char *product, int fd)
{
	t_gnl	*new_product;
	t_gnl	*last_product;

	last_product = gnl_ft_lstlast(store[fd]);
	new_product = (t_gnl *)malloc(sizeof(t_gnl));
	if (!new_product)
		return ;
	if (!last_product)
		store[fd] = new_product;
	else
		last_product->next = new_product;
	new_product->content = product;
	new_product->next = NULL;
}

char	*gnl_fetch_queue(t_gnl *store)
{
	int		queue_len;
	char	*next_queue;

	if (!store)
		return (NULL);
	queue_len = gnl_lstlen_till_newline(store);
	next_queue = (char *)malloc(sizeof(char) * (queue_len + 1));
	if (!next_queue)
		return (NULL);
	gnl_cpylst_to_str(store, next_queue);
	return (next_queue);
}

void	gnl_cutting_in(t_gnl **store)
{
	t_gnl	*last_product;
	t_gnl	*clean;
	int		i;
	int		j;
	char	*product;

	product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean = (t_gnl *)malloc(sizeof(t_gnl));
	if (!product || !clean)
		return ;
	last_product = gnl_ft_lstlast(*store);
	i = 0;
	j = 0;
	while (last_product->content[i] && last_product->content[i] != '\n')
		i++;
	while (last_product->content[i] && last_product->content[++i])
		product[j++] = last_product->content[i];
	product[j] = '\0';
	clean->content = product;
	clean->next = NULL;
	gnl_free_store(store, clean, product);
}

//END
