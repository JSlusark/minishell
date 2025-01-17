/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/17 11:27:52 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct s_msh
{
	char **ms_env; // Environment variables
	//char	**ms_env_export;
	int exit_code; // Exit code (suggested by copilot for error handling)
} t_msh;

typedef struct s_flags
{
	int	node_n;						// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int	redir_i;					// redir index
	int token_n;
	bool start_node;		// Flags minishell to start a new node, it is set to false after we init the new node and set to true when we end the new node.
	bool find_cmd;			// Flags minishell to find the command of the node: this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipestart;  	// Flags minishell to check also if pipe is the first token when checking for pipe errors. I set this flag to false when the first token is not a pipe.
	bool found_echo;
}		t_flags;

typedef struct s_redir				// linked list of redirections as 1 node can have 1 or more redirections, double linked might be useful perhaps?
{
	struct s_redir *prev;
	int				type;			// Type of redirection (REDIR_IN, REDIR_OUT, APPEND, hEREDOC)
	int				redir_i;		// used for printing
	char			*target_name;	// Target of the redirection -> the filename (for input, output and append) or delimiter name (for HEREDOC)
	int				fd;				// file descriptor
	struct s_redir *next;
} t_redir;

typedef struct s_cmd		// command struct, everything that is not seen as part of redirection struct goes here and are seen as arguments
{
	char	*cmd;			// 1st arg of the input, the executor then checks if it's a valid command
	char	**args;			// array of remaining arguments
	bool	option_n;		// a true/false flag that is put for echo to check and see if having to add a newline or not
} t_cmd;

typedef struct s_node_list
{
	t_msh *msh; // we need this to access the env variables and the exit code
	struct s_node_list *prev; //link to prev node
	t_cmd *cmd; // struct that has a command (1st arg), array of args (for the command/cmd), and flag n alert (for echo only)
	t_redir *redir;
	int node_i; //for printing
	int nodes_total;// for printing
	struct s_node_list *next;
} t_node_list;


/* ---- Function that parses the tokens into a linked list of nodes --- */

// MAIN PARSING FUNCTION - returns a node list (or null if error) to the main
t_node_list	*return_nodes(t_tokens *token_list, t_msh *msh);

// PARSES EACH TOKEN TO ASSIGN ITS FUNCTION INSIDE ITS NODE - *p contains data that allows us to do that
bool parse_token(t_flags *p, t_tokens **token, t_node_list **head, t_node_list **new_node); // iterates through each token to replicate how bash distrobute their role in the node
t_flags assign_data(); // stores data that we pass to the parse_token function to avoid norm error of sending more than 4 params to it

// NODE FUNCTIONS (CREATE, APPEND, END) - alloc_nodes.c creates node list
t_node_list	*init_new_node(int node_n, bool *start_node, t_msh *msh); // allocates a new node at the start of parsing or after we encounter a pipe
void	append_node(t_node_list **head, t_node_list *new_node); // appends current node to list as head or last node of the list
void	end_new_node(bool *start_node, t_node_list **head, t_node_list *new_node, t_tokens *token, int token_n); // ends new node when we encounter a pipe and alerts us that we have to start a new node

// PARSE NODE ERRORS - error_handling.c stops node creation and prints error to the terminal
bool	pipe_error(t_tokens *token, bool check_pipestart, t_node_list *head, t_node_list *new_node); // gives error when CL starts with pipe, pipe is followed by \n or anothe pipe
bool	redir_error(t_tokens *token); // gives an error to when redir symbol is followed by |, another redir symbol and \n
// bool	unknown_token(t_tokens *token, t_node_list *head, t_node_list * new_node); // gives errors with unknown tokens

// REDIR LIST CREATION - alloc_redir.c creates a linked list of redirection structs for each node
bool	parse_redir(t_tokens **token, t_node_list	*new_node, int *redir_i); // creates redir data to add to the node
t_redir	*init_new_redir(t_tokens **token); // allocates redirection struct and writes the redir type and target (token after the redir symbol) to the redir struct.
bool	add_target(t_tokens *token, t_redir *redir); // adds the token that follows the redirection symbol a target of the redirection
void	append_new_redir(t_redir **head_redir, t_redir *curr_redir); // appends the redir struct to the redir linked list

// CMD STRUCT CREATION - after we parsed pipes and redird we create the cmd struct and assign cmd, args and n_option (if the command is echo)
bool parse_rest(t_tokens **token, t_node_list *new_node, int token_n, t_flags **p);
bool alloc_cmd(t_node_list *curr_node, t_tokens *token, t_flags **p);
bool add_argument(char ***args, char *new_arg); // new function to allocat arg as array and not ll
void	add_option_n(t_tokens **token, t_node_list *new_node);

//FREEING FUNCTIONS FOR NODE AND MSH
void free_node_list(t_node_list *node_list);
void free_msh(t_msh *msh); // needs to be called independently from the free node list

/* ------------------------------ */
// NODE PRINTING AND DEBUGGING
void print_nodes(t_node_list *head);
void print_nodes_in_outfile(t_node_list *head);

// ECOMMUNICATION BETWEEN PARSING AND EXECUTION
void	exec_nodes(t_node_list	*node_list);

#endif



//Good resources that helped getting me into this and that will allow us to expand our logic:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c
// brainstorming and asking questions to chat_gpt
// testing command lines in bash
// google & youtube


