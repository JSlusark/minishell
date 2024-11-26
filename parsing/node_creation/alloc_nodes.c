/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:57:22 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/26 15:59:56 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void append_node(t_node **head, t_node *new_node)
{
	if(!(*head))
	{
		*head = new_node; // This updates a local copy of head
		new_node->prev = NULL;
	}
	else
	{
		t_node *last_node = *head; // we do this to traverse tthrough the list without affecting it
		while(last_node->next) // we traverse the list until we reach the node that has NULL as next node
			last_node = last_node->next;
		last_node->next = new_node; // we assign the new node as last in the list
		// last_node->next->next = NULL;
		new_node->prev = last_node; // we assign the 2nd last node as prev node of teh new node
	}
}

t_node *create_node(t_node *node_list)
{
	t_node *new_node = calloc(1, sizeof(t_node));
	if (!new_node)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return(NULL);
	}
	return(new_node);
}