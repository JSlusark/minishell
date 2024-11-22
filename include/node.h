/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/22 16:49:44 by jslusark         ###   ########.fr       */
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

typedef enum e_target_type
{
	TARGET_FILENAME, 		// 0 - if token_type of the target is word or cmd
	TARGET_PATHNAME, 		// 1 - if token is REL, ABS path (which can end or not with a file)
	TARGET_ENV_PATHNAME,	// 2 - if token is an env_variable (once we have the nodes we check if the env_var is a valid path, like $PATH/file for example)
	TARGET_DELIMITER		// 3 - if redir_type is HEREDOC
} t_target_type;

typedef struct s_redir
{
	struct s_redir *prev; // we need this so that the curr redir can communicate with the previous if a node had more than 1 redir
	int		redir_type;   // Type of redirection (REDIR_IN, REDIR_OUT, APPEND_OUT, hEREDOC)
	int		redir_i; // can be useful when we have more than 1 redirection in a node
	char	*target;		// Target is filename (for input, output and append) or delimiter (for HEREDOC)
	int		target_type;	// can be delimiter for heredoc, for else it can be file name or a valid path to a file (abs, relative or env_var like $PATH)
	int		target_token_type; // We store the target token type so we can use to understand what path is used in TARGET PATH_NAME
	struct s_redir *next; // we need this as a redirection can be followed by other redirections and interact with them

	// this input can be stored after we have the nodes and before/while executing - still nedd to check if good
	char	*exec_path; // the path where we have to execute the redir, comes from target if target_type is path or we assign it by default to home of shell
	char	*exec_file; // the file we have to execute on (or also create in some cases), comes from target, if target type is not word we have to get the last word in path (comes after last /)
	char	*file_input; // we can store everything together and then split in different lines after if input has \n
	char	**split_input; // we can store everything together and then split in different lines after if input has \n
	int flags; // flags that we pass to open(), depends on the redir type
	int fd; // we can store fd here for future use?
	bool close_fd; // Indicates if the fd should be closed after use.

} t_redir;

typedef struct s_args // list of tokens that follow the command token in the node and considered its arguments
{
	struct s_args *prev;   // Pointer to the prev argument in the list (adding it in case it can be useful in the future)
	int arg_type;         //anything that is not a command/builtin token or part of the redirection struct (file, redir type)
	char *arg_value;      // Value of the token (strings.. could it be also expandables and env variables?)
	struct s_args *next;   // Pointer to the next argument in the list
} t_args;

typedef struct s_cmd // the the first token thas is not redirection data (redirection symbol and file name) or pipe is seen by bash as the command of the node
{
	int		cmd_type;         // type of the token given us from the tokenizer, this will help us with execution and error handling (if the command is not an actual command)
	char	*cmd_value;       // what is the value of the commmand (echo, cd, exit, string_value etc)
} t_cmd;

//a node table is a linked list of nodes, we traverse each node as a double linked list.. why?
// we do it so that when we have to execure we can access each node
typedef struct s_node // A node typically has this data: command, command arguments, redirection data (redir symbol and file name) and pipe, a sequence of node commands is called command_list
{
	struct s_node *prev; // prev nodes can help
	t_cmd *cmd_data;
	t_redir *redir_data;
	t_args *cmd_args;
	bool	n_flag; // flag that tells echo not to append a new_line to the echoed args
	int		n_flag_n; // writes how many time -n flag to see if last arg should be -
	int	node_i;
	int	node_amount;// every node will store this data so we know how many pipes we have
	struct s_node *next;
} t_node;

// IMPORTANT: AN ABSTRACT SYNTAX TREE IS A SEQUENCE OF NODE LISTS THAT ARE LINKED THROUGH EACHOTHER WITH AN OPERATOR(&& or ||) or a DELIMITER (;)
// THEREFORE ONLY IN THE BONUS WE CREATE A REAL ABSTRACT SYNTAX TREE.
// WITHOUT THE BONUS, ANY OF OUR COMMANDS ARE GROUPED IN NODE COMMANDS IN A SINGLE NODE TABLE: so we do not need to return the ast struct written below.
/* typedef	struct s_ast // wrote this just to better clarify my node structure
{
	t_node			*curr_node_list; // the cmd table made of nodes and pipes
	t_operator		*operator_data; // the && and || operators and ; // the ; delimeter (contais the operator type and value and node to the next cmd table)
	t_node			*next_node_list; // the cmd table made of nodes and pipes
}	t_ast; // without bonus  t_ast will only return 1 cmd_line while the rest of the data is empty */


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
// brainstorming and asking questions to chat_gpt
// testing command lines in bash
// google


#endif
