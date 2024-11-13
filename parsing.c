/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 17:07:56 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse(t_mock *mock_token) // this function moves in a loop as while(1) from minishell
{
	int node_n = 1;
	int token_n = 0;
	int node_table = 1;
	int print_node_number = 1;  // Flag to print node number only once per node
	bool pipe_at_start = true; // flag to see if we start with pipe and therefore error
	printf(COLOR_GREEN"\n-----------------------------START OF TREE\n\n"COLOR_RESET);
	while (mock_token)
	{
		token_n++;
		if (print_node_number == 1)
		{
			printf(COLOR_RED"- NODE %i: \n"COLOR_RESET, node_n);
			print_node_number = 0; // Reset flag after printing the node number
		}
		if (mock_token->mock_type == PIPE)
		{
			if(!mock_token->next_token || pipe_at_start)
				printf("ERROR: Cannot start or end input with a pipe!\n"); // we check if pipe is folo
			else
			{
				printf(COLOR_RED"	%s\n"COLOR_RESET, mock_token->mock_value); // here w
				printf(COLOR_RED"	%s TOKEN %d: PIPE\n"COLOR_RESET, mock_token->mock_value, token_n); // here w
				printf(COLOR_RED"	%s\n"COLOR_RESET, mock_token->mock_value); // here w
				node_n++;
				print_node_number = 1;   // Set flag to print the new node number at the start of the next table
			}
		}
		else if (mock_token->mock_type == OPERATOR) // <----- ADDED THIS JUST TO SHOW BETTER AST CREATION
		{
				printf("\n-------------END OF NODE TABLE %d\n", node_table);
				// printf("\n_______________________________________\n\n");
				node_table++;
				printf(COLOR_RED"\n%s OPERATOR\n"COLOR_RESET, mock_token->mock_value); // here w
				// printf(COLOR_RED"	OPERATOR: %s \n"COLOR_RESET, mock_token->mock_value);
				// printf("\n_______________________________________\n");
				printf("\n-------------START OF NODE TABLE %d\n\n", node_table);
				printf("\n");
				node_n++;
				print_node_number = 1;   // Set flag to print the new node number at the start of the next table
		}
		else
		{
			pipe_at_start = false;
			printf(COLOR_BLUE"	TOKEN %d: "COLOR_RESET, token_n);
			printf("%s\n", mock_token->mock_value);
			// printf("	VALUE:%s, Type: %d \n", mock_token->mock_value, mock_token->mock_type);
		}
			mock_token = mock_token->next_token; // assigns the next mock token for next parsing iteration
	}
	printf(COLOR_GREEN"\n-----------------------------END OF TREE \n\n"COLOR_RESET);
	if (node_n < 1)
		printf("Our AST is made of just one node - a node is a command followed by arguments (strings, redirections, flags etc..)");
	if(node_n > 1)
		printf("Our AST is made of %d node tables: \nIn  this case the command table is a sequence of %d nodes linked with eachother through pipes\n", node_table, node_n);
	if(node_table > 1)
		printf("Our AST is made of %d node tables: \nEach node table is connected by && or || operators\n -----> THIS IS ONLY REQUIRED IN THE BONUS!!!! \n ", node_table);
	return NULL;
}
