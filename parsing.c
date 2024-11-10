/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 14:13:44 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h" // Assuming all your structs and enums are in node.h
#include "scanner.h" // For scanning tokens
#include "token.h" // For token definitions

// Forward declaration
static t_node *parse_command(t_scanner *scanner);
static t_node *parse_binary(t_scanner *scanner, t_token operator);


/*Primary parsing function that checks if there is a tokens and determines node type based on token returned from scanner. */
t_node	*parse(t_scanner *scanner)
{
	t_token	token;

	if (!scanner_has_next(scanner))
		return (NULL);
	token = scanner_peek(scanner);
	switch (token.type) // using switch just to simplify for now and use just echo as an example
	{
		case COMMAND:
			return parse_command(scanner);
		case PIPE:
		case REDIR_IN:
		case REDIR_OUT:
		case APPEND_OUT:
			return parse_binary(scanner, token);
		default:
			return (NULL); // To handle other token types or return error node
	}
}

/* Parses and returns a single command node with arguments or options.*/
static t_node	*parse_command(t_scanner *scanner)
{
	t_token			command_token;
	t_command_node	*cmd_node;
	t_token			next_token;
	t_node			*node;

	cmd_node = malloc(sizeof(t_command_node));
	command_token = scanner_next(scanner);
	if (!cmd_node)
		return (NULL);

	cmd_node->curr = &command_token;
	// Check for the next token as an argument or option (in order for a command to be valid we should add some functiosn to do that?)
	if (scanner_has_next(scanner))
	{
		next_token = scanner_peek(scanner);
		if (next_token.type == STRING_LITERAL || next_token.type == OPTION)
			cmd_node->next = &scanner_next(scanner);
	}
	// Create and return the COMMAND node
	node = malloc(sizeof(t_node));
	if (!node)
	{
		free(cmd_node);
		return NULL;
	}

	node->node_type = COMMAND;
	node->data.command_sequence = cmd_node;
	return (node);
}

/* Parses a binary operation (pipe or redirection). */
static t_node *parse_binary(t_scanner *scanner, t_token operator)
{
	// Advance past the operator token
	scanner_next(scanner);

	t_binary_node *bin_node = malloc(sizeof(t_binary_node));
	if (!bin_node) return NULL;

	// Parse the left and right nodes
	bin_node->node_l = parse(scanner);  // Left command
	bin_node->binary_operator = operator; // Operator token
	bin_node->node_r = parse(scanner);  // Right command or file

	// Create and return the BINARY node
	t_node *node = malloc(sizeof(t_node));
	if (!node) {
		free(bin_node);
		return NULL;
	}

	node->node_type = BINARY;
	node->data.pair_node = *bin_node;
	return node;
}
