/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:40:35 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/24 06:03:31 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//START
#include "../../headers/get_next_line_H/get_next_line.h"

int	gnl_search_newline(t_gnl *store)
{
	int	i;

	if (!store)
		return (0);
	while (store)
	{
		i = 0;
		while (store->content[i] && i < BUFFER_SIZE)
		{
			if (store->content[i] == '\n')
				return (1);
			i++;
		}
		store = store->next;
	}
	return (0);
}

t_gnl	*gnl_ft_lstlast(t_gnl *store)
{
	if (!store)
		return (NULL);
	while (store->next)
		store = store->next;
	return (store);
}

void	gnl_cpylst_to_str(t_gnl *store, char *queue)
{
	int	i;
	int	j;

	if (!store)
		return ;
	i = 0;
	while (store)
	{
		j = 0;
		while (store->content[j])
		{
			if (store->content[j] == '\n')
			{
				queue[i++] = '\n';
				queue[i] = '\0';
				return ;
			}
			queue[i++] = store->content[j++];
		}
		store = store->next;
	}
	queue[i] = '\0';
}

int	gnl_lstlen_till_newline(t_gnl *store)
{
	int	i;
	int	len;

	if (!store)
		return (0);
	len = 0;
	while (store)
	{
		i = 0;
		while (store->content[i])
		{
			if (store->content[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		store = store->next;
	}
	return (len);
}

void	gnl_free_store(t_gnl	**store, t_gnl *clean, char *product)
{
	t_gnl	*pop_up;

	if (!*store)
		return ;
	while (*store)
	{
		pop_up = (*store)->next;
		free((*store)->content);
		free(*store);
		*store = pop_up;
	}
	*store = NULL;
	if (clean->content[0])
		*store = clean;
	else
	{
		free(product);
		product = NULL;
		free(clean);
		clean = NULL;
	}
}

//END
