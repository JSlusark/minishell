/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/17 18:34:17 by jslusark         ###   ########.fr       */
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
	int	redir_type;   // Type of redirection (REDIR_IN, REDIR_OUT, APPEND_OUT, hEREDOC, Error redir etc.)
	char *file;          // Target file for input and append

	// other elements thayt we might need if we consider heredoc and other redirs;
	char *delimiter; // EOF - which is the first arg of the redir (not the cmd)
	char **input; // JUST FOR HERE_DOC: array that stores every heredoc line as a array[i] or the cmd_token args inside array[0]
	int flags; // flags that we pass to open(), depends on the redir type
	int fd; //if fd is null error and exit?
	struct s_redirection *next; // we need this as a redirection can be followed by other redirections and interact with them
} t_redirection;

typedef struct s_args // list of tokens that follow the command token in the node and considered its arguments
{
	int arg_type;         //anything that is not a command/builtin token or part of the redirection struct (file, redir type)
	char *arg_value;      // Value of the token (strings.. could it be also expandables and env variables?)
	struct s_args *arg_next;   // Pointer to the next argument in the list
} t_args;

typedef struct s_cmd
{
	int		cmd_type;         // builtin or command token, if not any of these we have error?
	char	*cmd_value;   // Pointer to the next argument in the list
} t_cmd;

typedef struct s_node // see if this works based on redi findings
{
	t_cmd *cmd_token; // created its own struct for the command token to keep things tidy and separate, the shell sees the first token as a command unless a redir is found
	t_redirection *redir;  // Input redirection, e.g., "< input.txt"
	t_args *cmd_args; // List of arguments following the command (list of tokens coming after the command)
	int pipe; // true or false - pipe will be part of the node, if pipe is true we have to check if we have another node
	// `echo hi > hello.txt  bye bye` <--- basically hi and byebye are part of the echo args here
} t_node;

typedef	struct  s_node_table //if next token is PIPE we create this
{
	t_node	curr_node;
	t_node	*next_node; // Pointer to the next command in the pipeline and its pipe(if it has one) - using struct keyword for recursive structs
	//if pipe true and next_cmds is null it is error (we cannot END a node table with a pipe)
	// if pipe true and next_cmd_node->next is null and cmd_node->next->pipe is false it means we have just one command following the first pipe and not more we need to consider after
}	t_node_table;

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


t_node_table	*parse(t_mock *mock_token); // mock version
t_mock *create_mock_tokens(char *input);


//Good resources that helped getting me into this and that will allow us to expand our logic:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c


#endif


// NOTES FOR ME:
// defining the diff redirs data ✅
// fix pipe handling
// adding commands and args?? <- doing now

// creating nodes, what i print in the parsing.c has to be printed actually AFTER i build these node
// what I am doing now is making sure i get the structure right before creating my nodes
// so printing the outcome i hve in my head will allow me to no do premature decisions in my code