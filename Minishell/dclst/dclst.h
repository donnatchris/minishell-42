/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:13:11 by christophed       #+#    #+#             */
/*   Updated: 2025/02/14 17:02:12 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCLST_H
# define DCLST_H

// Libraries
# include <stdlib.h>

// Structures
typedef struct s_dclst
{
	void			*data;
	struct s_dclst	*prev;
	struct s_dclst	*next;
}					t_dclst;

// Functions

// Create a new node with the given data
t_dclst	*dclst_create_node(void *data);

// Add a new node with the given data at the end of the list
t_dclst	*dclst_add_back(t_dclst **head, void *data);

// Add a new node with the given data at the beginning of the list
t_dclst	*dclst_add(t_dclst **head, void *data);

// Remove the specified node from the list
void	dclst_remove_node(t_dclst **head, t_dclst *node);

// Clear the entire list
void	dclst_clear(t_dclst **head);

// Count the number of nodes in the list
int		dclst_count_nodes(t_dclst *head);

// Find the position of the specified node in the list
int		dclst_find_node_pos(t_dclst *head, t_dclst *node);

// Find the node at the specified position in the list
t_dclst	*dclst_find_node_with_pos(t_dclst *head, int position);

// Move the specified node from the origin list to the destination list
void	dclst_move_node(t_dclst **origin, t_dclst **destination, t_dclst *node);

// Swap the positions of the two specified nodes in the list
int		dclst_swap_nodes(t_dclst **head, t_dclst *node1, t_dclst *node2);

#endif