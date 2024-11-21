/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 18:46:49 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// other than printing the node, what could be useful for execution is
// storing and printing the amount of redirections and arguments inside each node
// i want to work on redirection tbh as the structure might still need to be improved
// we leave piping for end?

void print_args(t_args *head)
{
	if (!head)
	{
		printf(COLOR_RED"		- t_args cmd_args:\n"COLOR_RESET);
		printf("			  - No args found from input\n");
		return;
	}
	// printf("HEYYYY\n");
	t_args *current = head;
	int index = 1; // Index to track the argument position in the list
	printf(COLOR_RED"		- t_args cmd_args:\n"COLOR_RESET);
	while (current)
	{
		printf(COLOR_BLUE"			ARG N_%d\n"COLOR_RESET, index);
		printf("			  - int type: %d\n", current->arg_type);
		if (current->arg_value)
			printf("			  - char *value: %s\n", current->arg_value);
		else
			printf("			  - char *value: (NULL)\n");
		current = current->next; // Move to the next argument in the list
		index++;
	}
}

void print_nodes(t_node *head)
{
	int n = 0;

	printf(COLOR_GREEN"\nRETURNING NODE LIST...\n"COLOR_RESET); // Print the node_i value
	t_node *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{
		n++;
		printf(COLOR_RED"	- NODE %d\n"COLOR_RESET, n); // Print the node_i value
		printf("		- int node_i: %d\n", curr->node_i); // Print the node_i value
		printf(COLOR_RED"		- t_cmd command_data:\n"COLOR_RESET); // Print the node_i value
		if (curr->cmd_data)
		{
			printf("				int cmd_type: %d\n", curr->cmd_data->cmd_type); // Print the node_i value
			printf("				char *cmd_value: %s\n", curr->cmd_data->cmd_value); // Print the node_i value
		}
		if (!curr->cmd_data)
			printf("		(NULL)\n"); // Print the node_i value
		print_args(curr->cmd_args);
		curr = curr->next; // Move to the next node
	}
	printf("\n	Total number of pipes: %d\n", n - 1); // Print the node_i value
	printf("	Total number of nodes: %d\n", n); // Print the node_i value
}