/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 22:58:53 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	"node.h"

/* It iterates from a list of tokens (check mock_data/createmocktokens and t_mock struct in node.h)
based on the token.type coming from our inputs it will execute commands and/or split them into different commands. */
/* Unsure if needing to initiate parsing based on the first token or if we shall first check if operation tokens are present before anything else.*/
t_node *parse(t_mock *mock_token)
{
	while (mock_token)
	{ // Loop through each token in the linked list
		switch (mock_token->mock_type) {
			case COMMAND:
				printf("\nFOUND TOKEN - COMMAND\n");
				break;
			case PIPE:
				printf("\nFOUND TOKEN - OPERATOR\n");
				break;
			default:
				printf("\nFOUND TOKEN - OTHER\n");
				break;
		}
		// Print the value for each token to verify it updates
		printf("Value: %s\n", mock_token->mock_value);
		printf("Type: %d\n\n", mock_token->mock_type);
		// Move to the next token in the list
		mock_token = mock_token->next_token;
	}

	return NULL; // Currently just returning NULL as no actual node structure is created and am literally unsure if we even need creating nodes at this point, will check further
}

/*
The functions commented below were built with the intent to create nodes out of tokens by iteratively scanning thorugh the *scanner.
We need to re-evaluate this approach as it was initially created by taking
into consideration the scanner functions (with scanner_peek and scanner_next)
which makes sense to use if we decide to parse iteratively thourgh the string.
But am wondering if the approach used with parsing the mock data can be easier and less complicated, especially because we do not to fully replicate
bash behaviour in our shell.
*/








/* Parses a single command with an optional argument or option.
  Example: "echo hello" */
// static t_node *parse_command(t_mock *mock_token)
// {
//     t_command_node *sequence;
//     t_node *node;

//     // Allocate memory for the command node structure
//     sequence = malloc(sizeof(t_command_node));
//     if (!sequence) {
//         return NULL; // Memory allocation failure
//     }

//     // Set the current command token
//     sequence->curr = malloc(sizeof(t_token));
//     if (!sequence->curr) {
//         free(sequence);
//         return NULL;
//     }
//     sequence->curr->type = mock_token->mock_type;
//     sequence->curr->lexeme.start = mock_token->mock_value;
//     sequence->curr->lexeme.length = strlen(mock_token->mock_value);

//     // Move to the next token
//     mock_token = mock_token->next_token;

//     // Check if there’s a valid argument or option following the command
//     if (mock_token && (mock_token->mock_type == STRING_LITERAL || mock_token->mock_type == OPTION))
//     {
//         sequence->next = malloc(sizeof(t_token));
//         if (!sequence->next) {
//             free(sequence->curr);
//             free(sequence);
//             return NULL;
//         }
//         sequence->next->type = mock_token->mock_type;
//         sequence->next->lexeme.start = mock_token->mock_value;
//         sequence->next->lexeme.length = strlen(mock_token->mock_value);
//     }
//     else
//     {
//         sequence->next = NULL; // No valid next token
//     }

//     // Create the main node for the command sequence
//     node = malloc(sizeof(t_node));
//     if (!node) {
//         free(sequence->curr);
//         free(sequence->next);
//         free(sequence);
//         return NULL;
//     }

//     node->node_type = COMMAND_N;
//     node->data.command_sequence = sequence;

// 	// printf("COMMAND NODE!!!!\n");
//     return node;
// }

// /* Parses a pipe command with two commands on each side of the pipe.
//  * Example: "echo hello | cat" */
// static t_node *parse_pipe_command(t_mock *mock_token)
// {
//     t_binary_node *pair;
//     t_node *container_node;

//     // Move past the PIPE token
//     mock_token = mock_token->next_token;

//     // Allocate memory for the binary node structure
//     pair = malloc(sizeof(t_binary_node));
//     if (!pair)
//         return NULL;

//     // Parse left command node
//     pair->node_l = parse_command(mock_token); // Left command
//     if (!pair->node_l) {
//         free(pair);
//         return NULL; // Failed to parse left command
//     }

//     // Set the operator for the binary node (PIPE)
//     pair->binary_operator.type = PIPE;
//     pair->binary_operator.lexeme.start = "|";
//     pair->binary_operator.lexeme.length = 1;

//     // Move to the next command after the pipe operator
//     mock_token = mock_token->next_token;

//     // Parse the right command node
//     if (mock_token && mock_token->mock_type == COMMAND)
//     {
//         pair->node_r = parse_command(mock_token); // Right command after the pipe
//         if (!pair->node_r) {
//             free(pair->node_l);
//             free(pair);
//             return NULL; // Failed to parse right command
//         }
//     }
//     else
//     {
//         free(pair->node_l);
//         free(pair);
//         return NULL; // No right command present
//     }

//     // Create the container node for the binary operation
//     container_node = malloc(sizeof(t_node));
//     if (!container_node)
//     {
//         free(pair->node_l);
//         free(pair->node_r);
//         free(pair);
//         return NULL;
//     }

//     container_node->node_type = BINARY_N;
//     container_node->data.binary_node = *pair;
//     free(pair); // Free the pair structure after copying its data
//     return container_node;
// }
