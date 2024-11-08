/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/08 18:17:51 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

/* Defines two types of nodes for the tree structure:
- BINARY: For operations with two sides (like pipes and redirections).
- SINGLE: For simple command sequences (like "echo hello"). */
typedef enum s_node_type
{
	BINARY,
	SINGLE,
}	t_node_type;

/* Represents a single command or a command sequence with arguments/options.
For example, "echo hello" where:
- curr represents the first token (e.g. echo).
- next represents the next tokens that are used following echo (e.g. "hello"). */
typedef struct s_command_node
{
	t_token	curr; // Main command token (type:"COMMAND" lexeme:"echo")
	t_token	next; // Argument or option that follows the command (type:"STRING" lexeme:"hello")
}	t_command_node;


/* Represents a binary operation with two sides, such as a pipe or redirection.
For example, "echo hello > output.txt" where:
- node_l represents the left command ("echo hello").
- binary_operator represents the ">" operator.
- node_r represents the right command or file ("output.txt"). */
typedef struct s_binary_node
{
	t_command_node	*node_l; // Left side of the operator (command or command sequence)
	t_token			binary_operator; // Operator token (e.g., "|", ">", "<")
	t_command_node	*node_r; // Right side of the operator (command or command sequence)
}	t_binary_node;


/* Uses a union to store either a binary operation (t_binary_node) or a single command sequence (t_command_node).
This allows a node to be either a simple command or a binary operation. */
typedef union s_node_value
{
	t_binary_node	pair_node; // Stores a binary operation node
	t_command_node	command_sequence; // Stores a single command sequence node
}	t_node_value;


/* Main node structure:
- node_type specifies if it's a BINARY or SINGLE node.
- data stores the actual node data, either a command sequence or a binary operation. */
typedef struct s_node
{
	t_node_type				node_type; // Type of node (BINARY or SINGLE)
	t_node_value			data; // Actual data for the node
}	t_node;


#endif
