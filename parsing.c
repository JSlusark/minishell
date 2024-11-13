/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 17:59:43 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse(t_mock *mock_token)
{
	int node_n = 1;
	int token_n = 0;
	int node_table = 1;
	int print_node_number = 1;   // Flag to print node number only once per node
	bool pipe_at_start = true;   // Flag to see if we start with a pipe and therefore error
	bool start_of_table_printed = false; // Flag to track "START OF NODE TABLE" printing

	printf(COLOR_GREEN"\n----------------START OF TREE-----------------\n\n"COLOR_RESET);

	while (mock_token)
	{
		token_n++;

		// Print node number at the start of each new node
		if (print_node_number == 1)
		{
			if (!start_of_table_printed)
			{
				printf("    ----START OF NODE TABLE %d------------\n\n", node_table);
				start_of_table_printed = true;
			}
			printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
			print_node_number = 0; // Reset flag after printing the node number
		}

		if (mock_token->mock_type == PIPE)
		{
			if (!mock_token->next_token || pipe_at_start)
				printf("ERROR: Cannot start or end input with a pipe!\n"); // Check for invalid pipe position
			else
			{
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value); // here w
				printf(COLOR_RED"		TOKEN %d: PIPE\n"COLOR_RESET, token_n); // here w
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value); // here w
				node_n++;
				print_node_number = 1;      // Reset to print new node number
				start_of_table_printed = true; // Assume table continues until we encounter an operator
			}
		}
		else if (mock_token->mock_type == OPERATOR) // <----- ADDED THIS JUST TO SHOW BETTER AST CREATION
		{
			printf("\n    ----END OF NODE TABLE %d-------------\n", node_table);
			node_table++;  // Increment table count
			printf(COLOR_BLUE"\n    TOKEN %d: %s\n\n"COLOR_RESET, token_n, mock_token->mock_value);
			printf("    ----START OF NODE TABLE %d------------\n\n", node_table);
			// Start a new node table and reset necessary flags
			node_n++;
			print_node_number = 1;  // Print node number at the start of the next table
			start_of_table_printed = true; // Table continues after operator
		}
		else
		{
			// General tokens (COMMAND, STRING, OPTION)
			pipe_at_start = false;
			printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
			printf(COLOR_BLUE"%s\n"COLOR_RESET, mock_token->mock_value);
		}

		mock_token = mock_token->next_token; // Move to the next token
	}
	printf("\n    ----END OF NODE TABLE %d-------------\n", node_table);
	printf(COLOR_GREEN"\n----------------END OF TREE-------------------\n\n"COLOR_RESET);

	// Summary of AST structure
	if (node_n == 1) {
		printf("Our TREE is made of just one node:\n a node is a command followed by arguments (strings, redirections, options, etc.)\n");
	} else if (node_table == 1) {
		printf("Our TREE is made of %d nodes connected by pipes within a single table.\n", node_n);
	} else {
		printf("Our TREE is made of %d node tables:\n Each node table is connected by && or || operators\n -----> THIS IS ONLY REQUIRED IN THE BONUS!!!! \n", node_table);
	}
	return NULL;
}
