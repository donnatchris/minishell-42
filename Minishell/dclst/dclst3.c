/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclst3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:38:36 by christophed       #+#    #+#             */
/*   Updated: 2025/02/14 17:37:16 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dclst.h"

// Function to update the prev pointers after having swapped 2 nodes
static void	update_prev_pointers(t_dclst *head)
{
	t_dclst	*current;

	current = head;
	if (!head)
		return ;
	while (current->next != head)
	{
		current->next->prev = current;
		current = current->next;
	}
	current->next->prev = current;
}

// Function to swap 2 adjacent nodes in the doubly circular linked list
static void	swap_adjacent_nodes(t_dclst *node1, t_dclst *node2)
{
	if (node1->next == node2)
	{
		node1->next = node2->next;
		node1->prev->next = node2;
		node2->next->prev = node1;
		node2->prev = node1->prev;
		node2->next = node1;
		node1->prev = node2;
	}
	else
	{
		node2->prev->next = node1;
		node1->next->prev = node2;
		node2->next = node1->next;
		node1->prev = node2->prev;
		node2->prev = node1;
		node1->next = node2;
	}
}

// Function to swap 2 non adjacent nodes in the doubly circular linked list
static void	swap_non_adjacent_nodes(t_dclst *node1, t_dclst *node2)
{
	t_dclst	*temp_next;
	t_dclst	*temp_prev;

	temp_next = node1->next;
	temp_prev = node1->prev;
	node1->prev->next = node2;
	node1->next->prev = node2;
	node2->prev->next = node1;
	node2->next->prev = node1;
	node1->next = node2->next;
	node1->prev = node2->prev;
	node2->next = temp_next;
	node2->prev = temp_prev;
}

// Function to swap 2 nodes in the doubly circular linked list
int	dclst_swap_nodes(t_dclst **head, t_dclst *node1, t_dclst *node2)
{
	if (!head || !*head || !node1 || !node2 || (node1 == node2))
		return (-1);
	if (*head == node1)
		*head = node2;
	else if (*head == node2)
		*head = node1;
	if (node1->next == node2 && node2->next == node1)
	{
		node1->prev->next = node2;
		node2->next->prev = node1;
		node1->next = node2->next;
		node1->prev = node2;
		node2->next = node1;
		node2->prev = node1->prev;
	}
	else if (node1->next == node2 || node2->next == node1)
		swap_adjacent_nodes(node1, node2);
	else
		swap_non_adjacent_nodes(node1, node2);
	update_prev_pointers(*head);
	return (0);
}

// Function to move a node from a doubly circular linked list
// to the top of another doubly circular linked list
void	dclst_move_node(t_dclst **origin, t_dclst**destination, t_dclst *node)
{
	if (node == *origin)
	{
		if ((*origin)->next == *origin)
			*origin = NULL;
		else
			*origin = node->next;
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	if (!*destination)
	{
		*destination = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		node->next = *destination;
		node->prev = (*destination)->prev;
		(*destination)->prev->next = node;
		(*destination)->prev = node;
		*destination = node;
	}
}
