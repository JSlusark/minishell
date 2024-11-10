#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	// TRIGGERS COMMAND NODES?
	COMMAND,        // Shell commands (e.g., "cd", "echo", "ls")
	PATH,           // Path values (e.g., "/usr/bin", "../")
	ENV_VAR,        // Environment variable (e.g., "$HOME", "$USER")
	STRING_LITERAL, // String literals in quotes (e.g., "hello world")
	BUILTIN,        // Built-in shell commands (e.g., "exit", "pwd", "export")
	OPTION,         // Command options (e.g., "-l", "-a")
	DELIMITERS, // ";" we may not need this? "hecho hello; echo jess" will print "hello echo jess"
	// TRIGGERS BINARY NODES?
	REDIR_IN,       // Input redirection ("<")
	REDIR_OUT,      // Output redirection (">")
	APPEND_OUT,     // Append redirection (">>")
	HEREDOC,        // Here-document redirection ("<<")
	PIPE,           // Pipe operator ("|")
	FILENAME,       // can we do echo file.txt ?? if so could be part of the command node triggering?
	D_QUOTES,
	S_QUOTES,
	UNKNOWN         // Any unrecognized or invalid token
} t_token_type;

typedef struct s_slice
{
	char *start; //Pointer to the start of the lexeme. (For 'echo' start is pointing to the 'e')
	size_t length; //Lexeme length.
}				t_slice;

typedef struct s_token
{
	t_token_type type;
	t_slice lexeme;
}			t_token;


// void print_token(const t_token token);


// WE COULD USE THIS AS PART OF THE PARSING FUNCTIONS PART?
// t_token take_command();
// t_token take_redir_in();
// t_token take_redir_out();
// t_token take_pipe();

#endif
