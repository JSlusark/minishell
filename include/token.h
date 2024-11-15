/*

Defines the types of tokens and the structure of a token used in the shell

 */


#ifndef TOKEN_H
#define TOKEN_H


typedef enum e_token_type
{
	OPERATOR,        // Operators like '>', '|'... etc. Not sure.
	WORD,           //Any string that can be classify later as cmd, or file or string...
	COMMAND,        // Shell commands (e.g., "cd", "echo", "ls")
	PATH,           // Path values (e.g., "/usr/bin", "../")
	//INTEGER,        // Integer literals (e.g., "123")
	OPTION,         // Command options (e.g., "-l", "-a")
	REDIR_IN,    // Input redirection ("<")
	REDIR_OUT,   // Output redirection (">")
	APPEND_OUT,     // Append redirection (">>")
	HEREDOC,        // Here-document redirection ("<<")
	PIPE,           // Pipe operator ("|")
	ENV_VAR,        // Environment variable (e.g., "$HOME", "$USER")
	//SUBSHELL,       // Subshell commands or groupings (e.g., "(command)")
	STRING_LITERAL, // String literals in quotes (e.g., "hello world")
	BUILTIN,        // Built-in shell commands (e.g., "exit", "pwd", "export")
	//LOGICAL_AND,    // Logical AND ("&&")
	//LOGICAL_OR,     // Logical OR ("||")
	//SEMICOLON,      // Command separator (";")
	DELIMITERS,
	FILENAME,
	D_QUOTES,
	S_QUOTES,
	END,
	UNKNOWN         // Any unrecognized or invalid token
} t_token_type;

typedef struct s_slice
{
	const char *start; //Pointer to the start of the lexeme. (For 'echo' start is pointing to the 'e')
	size_t length; //Lexeme length.
} t_slice;

typedef struct s_token
{
	t_token_type type;
	//char lexeme; //this needs to be an slice. To hold more than a char.
	t_slice lexeme;
} t_token;

t_token new_token (t_token_type type, char *start, size_t length);

/* t_token take_command();
t_token take_redir_in();
t_token take_redir_out();
t_token take_pipe(); */


void print_token(const t_token token);

//t_token end_token (t_scanner *self);
//t_token pipe_token (t_scanner *self);
//t_token redir_out_token (t_scanner *self);
//t_token redir_in_token (t_scanner *self);
//t_token word_token (t_scanner *self);
//t_token unknown_token (t_scanner *self);

#endif


