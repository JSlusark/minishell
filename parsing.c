/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 16:14:08 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // For token definitions and scanner function declarations

// Forward declaration for helper parsing functions
static t_node *parse_command(t_scanner *scanner);
static t_node *parse_binary(t_scanner *scanner, t_token operator);


/* Primary parsing function that initiates parsing based on the first token.
It checks if there is a next token and determines the node type based on the token returned from scanner. */
t_node	*parse(t_scanner *scanner) // called recursiveli i suppose?
{
	t_token	token;

	if (!scanner_has_next(scanner))
		return (NULL); // No tokens left to parse
	token = scanner_peek(scanner); 	// To see if token is present
	switch (token.type)
	{
		case COMMAND:
			return (parse_command(scanner, token)); // Handles command nodes, whall we also pass token?
		// case PIPE:
		// case REDIR_IN:
		// case REDIR_OUT:
		// case APPEND_OUT:
		// 	return (parse_binary(scanner, token)); // Handles binary operations - COMMAND LINES CAN NEVER START WITH THESE TOKENS THOUGH NO?
		default:
			return (NULL); // Placeholder for unsupported tokens or error handling
	}
}


/* If we peek and COMMAND Parses and returns a single command node with optional arguments or options. */
static t_node	*parse_command(t_scanner *scanner, t_token command)
{
	// Creates a linked list that stores the cmd_node and following options
	t_command_node	*sequence;
	t_node			*node;
	t_token			command_token;
	t_token			next_token;

	// Allocate memory for the command node structure
	sequence = malloc(sizeof(t_command_node));
	if (!sequence)
		return (NULL); // Handle memory allocation failure

	// Consume the command token
	command_token = scanner_next(scanner);
	sequence->curr = &command_token; // we could but function directly in here instead

	// Check if there’s a next token for an argument or option
	// we could probably add something that handles also other unexpected stuff like "echo |"?
	if (scanner_has_next(scanner))
	{
		next_token = scanner_peek(scanner);
		if (next_token.type == STRING_LITERAL || next_token.type == OPTION)
			sequence->next = &scanner_next(scanner); // Set the next token if it's a valid argument or option
		else
			sequence->next = NULL; // No valid next token
	}
	// Creates a main node for storing the command sequence and its sequential tokens
	node = malloc(sizeof(t_node));
	if (!node)
	{
		free(sequence);
		return (NULL);
	}
	node->node_type = COMMAND_N; // UNION BIT?
	node->data.command_sequence = sequence;
	return (node);
} // we will then have to check what is the command token type and based on that and then act upon it?



/// BINARY FOR LATER
/* Parses a binary operation (pipe or redirection).
This function creates a pair node, sepatared by the operator in the middle recursively parsing
the left and right sides of the operator. */
// static t_node	*parse_binary(t_scanner *scanner, t_token operator)
// {
// 	t_binary_node	*pair;
// 	t_node *container_node;

// 	// Advance past the operator token
// 	scanner_next(scanner);
// 	// Allocate memory for the binary node structure
// 	pair = malloc(sizeof(t_binary_node));
// 	if (!pair)
// 		return NULL; // Handle memory allocation failure
// 	pair->node_l = parse(scanner);  // Recursively parse for the left command or expression
// 	pair->pair_operator = operator; // Store the operator token "| "
// 	pair->node_r = parse(scanner);  // Recursively parse for the right command, expression, or file

// 	// Create a main node for the binary operation and assign the binary node to it
// 	container_node = malloc(sizeof(t_node));
// 	if (!node)
// 	{
// 		free(pair); // Clean up pair memory on failure
// 		return NULL;
// 	}
// 	container_node->node_type = BINARY_N; // UNION BIT?
// 	container_node->data.binary_node = *pair; // Assign the binary operation node data
// 	free(pair); // Free bin_node after copying data to the main node
// 	return node;
// }
