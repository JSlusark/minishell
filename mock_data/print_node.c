/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:03:24 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 22:29:32 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Prints the details of a token */
void print_token(t_token *token) {
	if (token) {
		printf("Token Type: %d, Value: %.*s\n", token->type, (int)token->lexeme.length, token->lexeme.start);
	}
}

/* Prints the details of a command node */
void print_command_node(t_command_node *command_node) {
	if (command_node) {
		printf("COMMAND Node:\n");
		printf("  Command: ");
		print_token(command_node->curr);

		if (command_node->next) {
			printf("  Argument: ");
			print_token(command_node->next);
		} else {
			printf("  Argument: None\n");
		}
	}
}

/* Prints the details of a binary node */
void print_binary_node(t_binary_node *binary_node) {
	if (binary_node) {
		printf("BINARY Node:\n");
		printf("  Left Command:\n");
		print_command_node(binary_node->node_l);

		printf("  Operator: ");
		print_token(&binary_node->binary_operator);

		printf("  Right Command:\n");
		print_command_node(binary_node->node_r);
	}
}

/* Prints the node based on its type */
void print_node(t_node *node) {
	if (!node) {
		printf("NULL Node\n");
		return;
	}

	if (node->node_type == COMMAND_N) {
		print_command_node(node->data.command_sequence);
	} else if (node->node_type == BINARY_N) {
		print_binary_node(&node->data.binary_node);
	} else {
		printf("Unknown Node Type\n");
	}
}
