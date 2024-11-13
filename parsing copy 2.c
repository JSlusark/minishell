/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 14:58:47 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NEED TO BETTER CHECK THIS OUT
/* int count_args(t_mock *mock_token) {
    int count = 0;
    while (mock_token && (mock_token->mock_type == COMMAND || mock_token->mock_type == STRING_LITERAL)) {
        count++;
        mock_token = mock_token->next_token;
    }
    return count;
}

// Function to parse a single command and return a COMMAND_NODE
t_node *get_cmd(t_mock **mock_token) {
    int arg_count = count_args(*mock_token);
    if (arg_count == 0) {
        return NULL;
    }

    // Allocate memory for the command node
    t_node *node = malloc(sizeof(t_node));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->type = COMMAND_NODE;

    // Allocate memory for arguments (array of strings)
    node->data.command.args = malloc((arg_count + 1) * sizeof(char *));
    if (!node->data.command.args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (*mock_token && ((*mock_token)->mock_type == COMMAND || (*mock_token)->mock_type == STRING_LITERAL)) {
        // Copy the argument to the command's args array
        node->data.command.args[i++] = strdup((*mock_token)->mock_value);
        *mock_token = (*mock_token)->next_token;
    }
    node->data.command.args[i] = NULL; // Null-terminate the args array

    return node;
} */



t_ast *parse(t_mock *mock_token) // this function moves in a loop as while(1) from minishell
{
	// t_node *root; // this will be the first command table and it will be created iteratevily while calling get_cmd
	// t_node *binary_node;
	// root = mock_token;
	// root = get_cmd(&mock_token); // will parse and regroup all not pipe tokens in a command list

	while (mock_token)
	{
		// printf("Value: %s\n", mock_token->mock_value);
		// printf("Type: %d\n\n", mock_token->mock_type);
		// // Move to the next token in the list
		// mock_token = mock_token->next_token;
		int node_n = 1;
		int is_node_table = 0;

		if (mock_token->mock_type == PIPE) // and if we created a first ready root?
		{
			if(mock_token->next_token == 'NULL')
			{
				printf("ERROR: cannot end a command with pipe!"); // we check if pipe is folo
			}
			else
			{
				is_node_table = 1; // we have more than 1 node because a pipe is present and there is a token after it
				printf("Token value: %s, token type: %d \n", mock_token->mock_value); // here w
				printf("PIPE: node ends which means we need to build a node_table\n"); // here w
			}
			// binary_node = malloc(sizeof(t_node)); // need to better understand how this loop will work
			// if (!binary_node)
			// {
			// 	perror("malloc");
			// 	exit(EXIT_FAILURE);
			// }
			// binary_node->type = BINARY_NODE;
			// binary_node->data.binary.left = root; //
			// mock_token = mock_token->next_token; // Move to PIPE token
			// binary_node->data.binary.operator = mock_token; //(pipe token)
		}
		// if (binary_node != NULL) // if we assigned the first part of the binary node and there is a mock token it means we will have the
		// {
		// 	// mock_token = mock_token->next_token; // Move past PIPE token to then process tokens for the right command
		// 	// binary_node->data.binary.right = get_cmd(&mock_token); // creating right command, binary will never be binary but can be bigger, keep in mind for later
		// 	// root = binary_node; // Update root to the new binary node
		// }
		// else
		{
			if(is_node_table == 1)
			{
				node_n++;
			}
			printf("Part of Node %i \n", node_n);
		}
			mock_token = mock_token->next_token; // assigns the next mock token for next parsing iteration
	}
	// if we have left and | operator of the binary node, but there are no more tokens it should be an error as command ends with |
	return NULL; // correct return below
	// 	return root;
}
