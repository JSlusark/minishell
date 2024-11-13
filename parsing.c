/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 18:05:02 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse(t_mock *mock_token)
{
	int node_n = 1;
	int token_n = 0;
	int print_node_number = 1;   // Flag to print node number only once per node
	bool pipe_at_start = true;   // Flag to see if we start with a pipe and therefore error

	while (mock_token)
	{
		token_n++;

		if (print_node_number == 1)
		{
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
			}
		}
		else
		{
			pipe_at_start = false;
			printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
			printf(COLOR_BLUE"%s\n"COLOR_RESET, mock_token->mock_value);
		}

		mock_token = mock_token->next_token; // Move to the next token
	}
	// Summary of AST structure
	if (node_n == 1) {
		printf("\n Our TREE is made of just one node:\n a node is a command followed by arguments (strings, redirections, options, etc.)\n");
	} else if (node_n > 1) {
		printf("\n Our TREE is made of %d nodes connected by pipes within a single node table.\n", node_n);
	}
	return NULL;
}
