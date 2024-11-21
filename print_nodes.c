/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 14:07:50 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_nodes(t_node *head)
{
	t_node *current = head; // Start with the head of the node list
	printf("HEYYYYYY\n"); // Print the node_i value
	// Traverse through the linked list
	while (current != NULL)
	{
		printf("Node index: %d\n", current->node_i); // Print the node_i value
		current = current->next; // Move to the next node
	}
}