/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 15:29:11 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
// The scanning function (which we can also call tokenizer), should return us a linked list of tockens needed by our parsing function, just as the t_mock struct below
typedef struct s_mock
{
	int mock_type;         // Type of the token, e.g., COMMAND, STRING_LITERAL, etc.
	char *mock_value;      // Value of the token, e.g., "echo", "hello"
	struct s_mock *next_token; // Pointer to the next token in the linked list
}			t_mock;

typedef struct s_redirection
{
	struct s_redirection *prev; // we need this so that the curr redir can communicate with the previous if a node had more than 1 redir
	int	redir_type;   // Type of redirection (REDIR_IN, REDIR_OUT, APPEND_OUT, hEREDOC)
	char *file_name;          // Target file for input, output and append

	// other elements thayt we might need if we consider heredoc and other redirs;
	// char *delimiter; // we use this for HEREDOC instead than *file
	// char **file_input; // array that stores every heredoc line as a array[i] or the cmd_token args inside array[0]
	// int flags; // flags that we pass to open(), depends on the redir type
	// int fd; //we can store fd here for future use?
	struct s_redirection *next; // we need this as a redirection can be followed by other redirections and interact with them
} t_redirection;

typedef struct s_args // list of tokens that follow the command token in the node and considered its arguments
{
	struct s_args *arg_prev;   // Pointer to the next argument in the list
	int arg_type;         //anything that is not a command/builtin token or part of the redirection struct (file, redir type)
	char *arg_value;      // Value of the token (strings.. could it be also expandables and env variables?)
	struct s_args *arg_next;   // Pointer to the next argument in the list
} t_args;

typedef struct s_cmd // the the first token thas is not redirection data (redirection symbol and file name) or pipe is seen by bash as the command of the node
{
	int		cmd_type;         // type of the token given us from the tokenizer, this will help us with execution and error handling (if the command is not an actual command)
	char	*cmd_value;       // what is the value of the commmand (echo, cd, exit, string_value etc)
} t_cmd;

//a node table is a linked list of nodes, we traverse each node as a double linked list.. why?
// we do it so that when we have to execure we can access each node
typedef struct s_node // A node typically has this data: command, command arguments, redirection data (redir symbol and file name) and pipe
{
	struct s_node *prev; // prev nodes can help
	t_cmd *cmd_data;
	t_redirection *redir;
	t_args *cmd_args;
	// bool pipe;
	int	node_i;
	int	node_amount;// every node will store this data so we know how many pipes we have
	struct s_node *next;
} t_node;

// typedef	struct  s_node_table //if next token is PIPE we create this
// {
// 	// example: "echo hi > hello.txt bye bye | cat"
// 	t_node	curr_node; // Current node of teh table "echo hi > hello.txt bye bye |" (the node has a command "echo", 3 args "echo, bye, bye", redir data "> file.txt" and a pipe "|")
// 	t_node	*next_node; // Pointer to the next node "cat"  (the node has only a command cat, no args, redirections or pipes)
// 	//int	node_n; //to see if there are nodes that we need to pipe

// 	// example: "echo hi > hello.txt bye bye |"
// 	// here curr_node->pipe == true and next_node == NULL, so bash asks input fro the use to write the next commands
// 	// example: "echo hi > hello.txt bye bye"
// 	//here curr_node->pipe == false and next_node == NULL it means we have just one node in the node table
// }	t_node_table;

// IMPORTANT: AN ABSTRACT SYNTAX TREE IS A SEQUENCE OF NODE TABLES THAT ARE LINKED THROUGH EACHOTHER WITH AN OPERATOR(&& or ||) or a DELIMITER (;)
// THEREFORE ONLY IN THE BONUS WE CREATE A REAL ABSTRACT SYNTAX TREE.
// WITHOUT THE BONUS, ANY OF OUR COMMANDS ARE GROUPED IN NODE COMMANDS IN A SINGLE NODE TABLE: so we do not need to return the ast struct written below.
/* typedef	struct s_ast // wrote this just to better clarify my node structure
{
	t_node_table	curr_table; // the cmd table made of nodes and pipes
	// if we do the bonus the actual tree is built by considering the
	t_conjuction		table_conjunction_op; // the && and || operators and ; // the ; delimeter (contais the operator type and value and node to the next cmd table)
	t_node_table	*next_table;
}	t_ast; // without bonus  t_ast will only return 1 cmd_table while the rest of the data is empty */


t_node	*parse(t_mock *mock_token); // mock version
// t_node_table	*parse(t_tokens *tokens); // definitive version
t_mock			*create_mock_tokens(char *input);
void			free_mock_tokens(t_mock *head);

//freeing functions for node allocation data
void free_node_list(t_node *node_list);
void print_nodes(t_node *head);

//Good resources that helped getting me into this and that will allow us to expand our logic:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c


#endif


// DOING NOW:
// showing how bash interprets redirections ✅ (need to check better for input redir)
// showing how bash inteprets commans and args in a node ✅
// fix pipe handling (if node starts with pipe it is error, but if nod ends with pipe it is not an error unless pipe comes right after redir symbol)


// TO DO LATER, after making sure about bash token interpretation:
// Use the logic in parsing.c to create nodes in the command table
// print the nodes that we create from the parsin in a similar style i have now



///FUNCTIONS

// create table --- before loop allocate memory for the table ()
// create node --- if token loop happens and when node flag is true
// create redir struct
// create command struct
// create arg liked list sruct and collect args in the loop

// free functions