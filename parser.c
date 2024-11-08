/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:49:20 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/08 16:53:18 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void* check_outofmemory(void *ptr, char *file, int number)
{
	if (ptr == NULL) {
		// If memory allocation failed, print an error message and exit
		fprintf(stderr, "%s:%d Out of Memory", file, number);
		// remember to free anything we have to free before exiting!!
		exit(EXIT_FAILURE);
	}
	return ptr;  // Return the allocated pointer if successful
}

// Node creation function
t_node	*create_node(t_token token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

// function that groups nodes together to create a tree?
void attach_nodes_to_tree (t_node *tree, t_node *left_node, t_node *right_node)
{
	if (tree)
	{
		tree->left = left_node;
		tree->right = right_node;
	}
}

// We will use the parsing recursively scan and process each token inside nodes
// We need to consider if creating a double linked list of connected tokens will be a better approach
// as it might simplify how we iterate though tokens compared to this approach
t_node	*parse_tree(t_scanner *scanner)
{
	t_token	token;
	t_node	*node;

	if (!scanner_has_next(scanner))
		return (NULL);

	token = scanner_next(scanner);
	node = create_node(token);


	// HONESTLY USING IF/ELSE STATEMENDS FOR EVERY TOKEN TYPE DOES NOT SEEM IDEAL leaving this anyway for later reference and adjustments
	// Handle different token types
	if (token.type == COMMAND)
	{
		// Command node with potential arguments
		if (scanner_has_next(scanner)) {
			t_token next_token = scanner_peek(scanner);

			if (next_token.type == STRING_LITERAL || next_token.type == OPTION)
			{
				// Attach the next token as the right child (argument or option)
				scanner_next(scanner);  // Advance the scanner
				node->right = create_node(next_token);
			}
		}
	}
	else if (token.type == PIPE)
	{
		// If we encounter a PIPE, set left and right commands
		node->left = parse_tree(scanner);  // Left command
		node->right = parse_tree(scanner); // Right command
	}
	else if (token.type == REDIRECT_IN || token.type == REDIRECT_OUT)
	{
		// Handle redirection (attach the target file as right child)
		if (scanner_has_next(scanner)) {
			t_token file_token = scanner_next(scanner);
			if (file_token.type == FILENAME) {
				node->right = create_node(file_token);
			}
		}
	}
	// // Add more token handling as needed (e.g., APPEND_OUT, HEREDOC, etc.)

	return (node);
}
