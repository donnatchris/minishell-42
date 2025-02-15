/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclst1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:58:54 by christophed       #+#    #+#             */
/*   Updated: 2025/02/15 16:22:45 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dclst.h"

// Function to create a new node in the doubly circular linked list
t_dclst	*dclst_create_node(void *data)
{
	t_dclst	*new;

	new = (t_dclst *) malloc(sizeof(t_dclst));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = new;
	new->prev = new;
	return (new);
}

// Function to insert a new node at the end of the doubly circular linked list
t_dclst	*dclst_add_back(t_dclst **head, void *data)
{
	t_dclst	*new;

	new = dclst_create_node(data);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
	return (new);
}

// Function to insert a new node at the start of the doubly circular linked list
t_dclst	*dclst_add(t_dclst **head, void *data)
{
	t_dclst	*new;

	new = dclst_create_node(data);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
		*head = new;
	}
	return (new);
}

// Function to remove a node from the doubly circular linked list
void	dclst_remove_node(t_dclst **head, t_dclst *node)
{
	if (head && *head && node)
	{
		if (node->data)
			free(node->data);
		if (node == *head)
		{
			if ((*head)->next == *head)
			{
				free (*head);
				*head = NULL;
				return ;
			}
			*head = node->next;
		}
		node->next->prev = node->prev;
		node->prev->next = node->next;
		free(node);
	}
}

// Function to clear the entire doubly circular linked list
void	dclst_clear(t_dclst **head)
{
	if (!head)
		return ;
	while (*head)
		dclst_remove_node(head, *head);
	free(head);
}
