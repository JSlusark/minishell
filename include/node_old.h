/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/11 16:32:27 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

// PREVIOUS NODES, WILL CHANGE AND IMPROVE AS I MAKE A SENSE OUT OF WHAT I AM
// DOING WITH HANDLING TOKENS AND BUILDING NODES

/* Defines two types of nodes for the tree structure:
- BINARY_N: For operations with two sides (like pipes and redirections).
- COMMAND_N: For simple command sequences (like "echo hello"). */
typedef enum s_node_type
{
	BINARY_N,
	COMMAND_N,
}	t_node_type;

/* Represents a single command or a command sequence with arguments/options.
For example, "echo hello" where:
- curr represents the first token (e.g. echo).
- next represents the next tokens that are used following echo (e.g. "hello"). */
typedef struct s_command_node
{
	t_token	*curr; // Main command token (type:"COMMAND_N" lexeme:"echo")
	t_token	*next; // Argument or option that follows the command (type:"STRING" lexeme:"hello")
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
	t_binary_node	binary_node; // Stores a binary operation node
	t_command_node	*command_sequence; // Stores a single command sequence node
}	t_node_value;


/* Main node structure:
- node_type specifies if it's a BINARY_N or COMMAND_N node.
- data stores the actual node data, either a command sequence or a binary operation. */
typedef struct s_node
{
	t_node_type				node_type; // Type of node (BINARY_N or COMMMAND_N)
	t_node_value			data; // Actual data for the node
}	t_node;


// FUNCTIONS AND DATA USED FOR MOCKED PARSING - I will need you to provide me the following struct of tokens perhaps
typedef struct s_mock {
    int mock_type;         // Type of the token, e.g., COMMAND, STRING_LITERAL, etc.
    char *mock_value;      // Value of the token, e.g., "echo", "hello"
    struct s_mock *next_token; // Pointer to the next token in the linked list
} t_mock;
t_node	*parse(t_mock *mock_token); // mock version
t_mock *create_mock_tokens(char *input);

// FINDING OUT NODES FROM ANOTHER PROJECT

//Sources:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c

// typedef struct s_redir // can we use this instead than t_list inside t_cmd?
// {
//   int type;
// //   struct cmd *cmd;
//   char *file;
//   char *efile;
//   int mode;
//   int fd;
// }	t_redir;

// typedef struct s_cmd // contains tokensare r
// {
// 	t_list	*tokens;
// 	t_redir	*redirections;
// }			t_cmd;

// typedef struct s_list
// {
// 	void		*data;
// 	t_list		*next;

// }			t_list;

// void add_to_list(t_redir redirection_list, ft_lstnew(redir));

#endif
