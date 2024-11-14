/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/14 18:35:31 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_table *parse(t_mock *mock_token)
{
	int node_n = 1;
	int token_n = 0;
	int print_node_number = 1;   // Flag to print node number only once per node
	bool pipe_at_start = true;   // Flag to see if we start with a pipe and therefore error, we also have to include redir into this flag!!!

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
				printf("ERROR: Cannot start or end node with a pipe!\n"); // Check for invalid pipe position
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
			pipe_at_start = false; // needs to change as also we cannot start with redir as well
			if (mock_token->mock_type == REDIR_IN || mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT || mock_token->mock_type == HEREDOC)
			{
				// printing this by just considering output redirection outome but
				// we might probably need differnet cases for every redir type
				printf(COLOR_BLUE"			- REDIR:\n"COLOR_RESET);
				printf(COLOR_BLUE"			  TOKEN %d:"COLOR_RESET, token_n);
				printf("%s\n", mock_token->mock_value);
				if(mock_token->next_token == NULL) // certanly every redir type has to be always followed by a token
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					break;
				}
				if(mock_token->next_token != NULL) // certanly every redir type has to be always followed by a token
				{
					token_n++;
					mock_token = mock_token->next_token;
					if (mock_token->mock_type == PIPE || mock_token->mock_type == REDIR_IN
						|| mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT
						|| mock_token->mock_type == HEREDOC)
					{
						printf(COLOR_RED"ERROR: redirection cannot be immediately followed by pipes or other redirections \n"COLOR_RESET);
						break;
					}
					printf(COLOR_BLUE"			  TOKEN %d:"COLOR_RESET, token_n);
					printf("%s\n", mock_token->mock_value);
				}
			}
			else
			{
				printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
				printf("%s\n", mock_token->mock_value);
			}
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
