#ifndef PARSER_H
#define PARSER_H

#define BOUNDS " |><" // scared of adding \t and \n
#define QUOTES "\'\""
#define EXP_LIMIT "!@#$%%^&*()-+=[]{}|\\:;'\"/<>,.`~ "
typedef enum e_token_type // good to have an order like below
{
	REDIR_IN,       		// 5 Input redirection ("<")
	REDIR_OUT,      		// 6 Output redirection (">")
	APPEND,     		// 7 Append redirection (">>")
	HEREDOC,        		// 8 Here-document redirection ("<<")
	PIPE,           		// 9 Pipe operator ("|")
	ARG,         			//  CAL IT NQ_ARG? 12 Any letter or number that is not surrounded in " " and '', after we create the tokens and nodes, we need a function that will see if the word is an external command or just a word
	INVALID,
} t_token_type;

typedef struct s_tokens
{
	char *value;
	t_token_type type;
	struct s_tokens *next;
} t_tokens;


typedef struct s_msh
{
	char **ms_env; // Environment variables
	//char	**ms_env_export;
	int exit_code; // Exit code (suggested by copilot for error handling)
	int prev_exit;  /// the exit code returned from the previous execution
	// MOVED from t_flags avoid passing too many params in parse nodes
	int	node_n;						// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int	redir_i;					// redir index
	int token_n;
	bool start_node;		// Flags minishell to start a new node, it is set to false after we init the new node and set to true when we end the new node.
	bool find_cmd;			// Flags minishell to find the command of the node: this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipestart;  	// Flags minishell to check also if pipe is the first token when checking for pipe errors. I set this flag to false when the first token is not a pipe.
	bool found_echo;
} t_msh;

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
	int fd_in; // file descriptor for input
	int fd_out; // file descriptor for output
	t_msh *msh; // we need this to access the env variables and the exit code
	struct s_node_list *prev; //link to prev node
	t_cmd *cmd; // struct that has a command (1st arg), array of args (for the command/cmd), and flag n alert (for echo only)
	t_redir *redir;
	int node_i; //for printing
	int nodes_total;// for printing
	struct s_node_list *next;
} t_node_list;

/* _____________TOKENS FUNCTIONS_____________ */

// return_tokens.c - main function
t_tokens *return_tokens(char *input, t_msh *msh);
t_tokens *tokenize(char *input, int *i, t_msh *msh, t_tokens *tokens);

// allocate_tokens.c - creates a linked list of tokens and frees it
void append_token(t_tokens **head, t_tokens *new_token);
t_tokens *create_token(const char *value, int type);
void free_tokens(t_tokens *head);

// handle_invalid.c - handles characters that are part of the bonus <----------- unsure if we need this tbh
bool invalid_char(char *input, int i);

// tokenize_bounds.c : creates and appends tokens for | > < << and >>
bool valid_bound(char *input, int *i, t_tokens **tokens);
void handle_left(char *input, int *i, t_tokens **tokens);
void handle_right(char *input, int *i, t_tokens **tokens);

// tokenize strings (anything between " ", ' ' and any character that is not divided by a space, pipe or redirection symbol)
void parse_string(char *input, int *i, t_msh *msh, char *buff); // main function that checks interaction with quotes, expansiona and characters
void quoted_buff(char *input, int *i, t_msh *msh, char *buff);
bool empty_quoted(int *i, char *input); // I NEED ALSO TO MANAGE """""" CASE - should be easy
void unquoted_buff(char *input, int *i, t_msh *msh, char *buff);
// handle_expansions.c
char *find_envar(char *var, char **env); // finds only the var, does not expand
void	expand_to_buff(char *expansion, char *buff, int *len, t_msh *msh);
void collect_expansion(char *input, int *i, char *buff, t_msh *msh);

// stops buffer collection and if no error found appends node
bool stop_buffer(char *input, int *i, char *buff, t_msh *msh);

//debugging
void print_tokens(t_tokens *tokens);

/* _____________NODES FUNCTIONS_____________ */

// MAIN PARSING FUNCTION - returns a node list (or null if error) to the main
t_node_list	*return_nodes(t_tokens *token_list, t_msh *msh);

// PARSES EACH TOKEN TO ASSIGN ITS FUNCTION INSIDE ITS NODE - *p contains data that allows us to do that
bool parse_token(t_msh *msh, t_tokens **token, t_node_list **head, t_node_list **new_node); // iterates through each token to replicate how bash distrobute their role in the node
void assign_data(t_msh); // stores data that we pass to the parse_token function to avoid norm error of sending more than 4 params to it

// NODE FUNCTIONS (CREATE, APPEND, END) - alloc_nodes.c creates node list
t_node_list	*init_new_node(int node_n, bool *start_node, t_msh *msh); // allocates a new node at the start of parsing or after we encounter a pipe
void	append_node(t_node_list **head, t_node_list *new_node); // appends current node to list as head or last node of the list
void	end_new_node(bool *start_node, t_node_list **head, t_node_list *new_node); // ends new node when we encounter a pipe and alerts us that we have to start a new node

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
bool parse_rest(t_tokens **token, t_node_list *new_node, t_msh **msh);
bool alloc_cmd(t_node_list *curr_node, t_tokens *token, t_msh **msh);
bool add_argument(char ***args, char *new_arg); // new function to allocat arg as array and not ll
void add_option_n(t_tokens **token, t_node_list *new_node);

//FREEING FUNCTIONS FOR NODE AND MSH
void free_msh(t_msh *msh); // needs to be called independently from the free node list
void free_node_list(t_node_list *node_list);
void	free_cmd_struct(t_cmd *cmd);
void	free_redir_list(t_redir *head);

// NODE PRINTING AND DEBUGGING
char	*return_token_enum(int token_type);
char	*return_target_enum(int redir_type);
void	print_nodes(t_node_list *head);
void	print_exit_codes(t_msh	*msh);
void	print_null_cmd(void);
void	print_cmd_struct(t_cmd *cmd);
void	print_redir(t_redir *head);
void	print_nodes_file(t_node_list *head);
void	print_exit_codes_file(t_msh	*msh);
void	print_null_cmd_file(void);
void	print_cmd_struct_file(t_cmd *cmd);
void	print_redir_file(t_redir *head);

// COMMUNICATION BETWEEN PARSING AND EXECUTION
void	exec_nodes(t_node_list	*node_list);
#endif
