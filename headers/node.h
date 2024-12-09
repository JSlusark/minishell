/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/09 13:42:34 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct s_flags
{
	int	node_n;						// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int	redir_i;					// redir index
	int token_n;
	bool start_node;		// Flags minishell to start a new node, it is set to false after we init the new node and set to true when we end the new node.
	bool find_cmd;			// Flags minishell to find the command of the node: this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipestart;  	// Flags minishell to check also if pipe is the first token when checking for pipe errors. I set this flag to false when the first token is not a pipe.
}		t_flags;

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
	int		type;   // Type of redirection (REDIR_IN, REDIR_OUT, APPEND_OUT, hEREDOC)
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
	int type;         //anything that is not a command/builtin token or part of the redirection struct (file, redir type)
	char *value;      // Value of the token (strings.. could it be also expandables and env variables?)
	struct s_args *next;   // Pointer to the next argument in the list
} t_args;

typedef struct s_cmd // the the first token thas is not redirection data (redirection symbol and file name) or pipe is seen by bash as the command of the node
{
	int		type;         // type of the token given us from the tokenizer, this will help us with execution and error handling (if the command is not an actual command)
	char	*value;       // what is the value of the commmand (echo, cd, exit, string_value etc)
} t_cmd;

//a node table is a linked list of nodes, we traverse each node as a double linked list.. why?
// we do it so that when we have to execure we can access each node
typedef struct s_node_list // A node typically has this data: command, command arguments, redirection data (redir symbol and file name) and pipe, a sequence of node commands is called command_list
{
	struct s_node_list *prev; // prev nodes can help
	t_cmd *cmd; // actually we may not need a struct with cmd, just the value might be enough because of the logic wrote in the execution file
	t_redir *redir;
	t_args *args;
	int	node_i;
	struct s_node_list *next;
	//not sure yet but we have to find a way to handle -n flag
	bool		option_n; // checks if we have a flag
	int	nodes_total;// every node will store this data so we know how many pipes we have
} t_node_list;

// This would be needed if we decide to do the bonus
/* typedef	struct s_ast // wrote this just to better clarify my node structure
{
	t_node			*curr_node_list; // the cmd table made of nodes and pipes
	t_operator		*operator_data; // the && and || operators and ; // the ; delimeter (contais the operator type and value and node to the next cmd table)
	t_node_list			*next_node_list; // the cmd table made of nodes and pipes
}	t_ast; // without bonus  t_ast will only return 1 cmd_line while the rest of the data is empty */


/* ---- Function that parse the tokens into a linked list of nodes --- */

// MAIN PARSING FUNCTION - returns a node list (or null if error) to the main
t_node_list	*return_nodes(t_token_list *token_list);

// PARSES EACH TOKEN TO ASSIGN ITS FUNCTION INSIDE ITS NODE - *p contains data that allows us to do that
bool parse_token(t_flags *p, t_token_list **token, t_node_list **head, t_node_list **new_node); // iterates through each token to replicate how bash distrobute their role in the node
t_flags assign_data(); // stores data that we pass to the parse_token function as we cannot send more than 4 params to it

// NODE FUNCTIONS (CREATE, APPEND, END) - alloc_nodes.c creates node list
t_node_list	*init_new_node(int node_n, bool *start_node); // allocates a new node at the start of parsing or after we encounter a pipe
void	append_node(t_node_list **head, t_node_list *new_node); // appends current node to list as head or last node of the list
void	end_new_node(bool *start_node, t_node_list **head, t_node_list *new_node, t_token_list *token, int token_n); // ends new node when we encounter a pipe and alerts us that we have to start a new node

// PARSE NODE ERRORS - error_handling.c stops node creation and prints error to the terminal
bool	unknown_token(t_token_list *token); // gives errors with unknown tokens
bool	pipe_error(t_token_list *token, bool check_pipestart); // gives error when CL starts with pipe, pipe is followed by \n or anothe pipe
bool	redir_error(t_token_list *token); // gives an error to when redir symbol is followed by |, another redir symbol and \n

// REDIR LIST CREATION - alloc_redir.c creates a linked list of redirection structs for each node
bool	parse_redir(t_token_list **token, t_node_list	*new_node, int *redir_i); // creates redir data to add to the node
t_redir	*init_new_redir(t_token_list **token); // allocates redirection struct and writes the redir type and target (token after the redir symbol) to the redir struct.
bool	add_target(t_token_list *token, t_redir *redir); // adds the token that follows the redirection symbol a target of the redirection
void	append_new_redir(t_redir **head_redir, t_redir *curr_redir); // appends the redir struct to the redir linked list

// PARSES THE COMMAND, OPTIONS AND ARGUMENTS OF A NODE
bool parse_rest(bool *find_cmd, t_token_list **token, t_node_list *new_node, int token_n);
//Assigns token as command of the node
bool alloc_cmd(t_node_list *curr_node, t_token_list *token);
//Flags if option -n is present and handles order which is written on the CLI
void	check_option(t_token_list **token, t_node_list *new_node);
//Assigns token as arg of the node and appends to the arg list
t_args *init_new_arg(t_token_list *token);
void append_new_arg(t_args **args, t_args *new_arg);

//Frees the node list at evert error and at end of the execution
void free_node_list(t_node_list *node_list);

/* ------------------------------ */


//My mock tocken_list creation functions
t_token_list			*create_mock_tokens(char *input);
void			free_mock_tokens(t_token_list *head);

// Printing and debugging functions (we comment or remove them from our code when ready to submit)
void print_nodes(t_node_list *head);

// exec test
void	exec_node(t_node_list	*node_list);

#endif



//Good resources that helped getting me into this and that will allow us to expand our logic:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c
// brainstorming and asking questions to chat_gpt
// testing command lines in bash
// google & youtube


