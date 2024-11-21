/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 16:03:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// other than printing the node, what could be useful for execution is
// storing and printing the amount of redirections and arguments inside each node
// i want to work on redirection tbh as the structure might still need to be improved
// we leave piping for end?

void print_nodes(t_node *head)
{
	int n = 1;

	printf(COLOR_GREEN"\nRETURNING NODE LIST...\n"COLOR_RESET); // Print the node_i value
	t_node *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{

		printf(COLOR_RED"	- NODE %d\n"COLOR_RESET, n++); // Print the node_i value
		printf("		- int node_i: %d\n", curr->node_i); // Print the node_i value
		if (curr->cmd_data)
			printf("		- t_cmd command_data:\n			int type: %d\n			char *value: %s\n", curr->cmd_data->cmd_type, curr->cmd_data->cmd_value); // Print the node_i value
		if (!curr->cmd_data)
			printf("Node command: NULL\n"); // Print the node_i value
		curr = curr->next; // Move to the next node
	}
	printf("	Total number of pipes: %d\n", n - 1); // Print the node_i value
	printf("	Total number of nodes: %d\n", n); // Print the node_i value
}