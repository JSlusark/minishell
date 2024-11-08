#ifndef TOKEN_H
#define TOKEN_H

typedef enum e_token_type
{
	COMMAND,        // Shell commands (e.g., "cd", "echo", "ls")
	PATH,           // Path values (e.g., "/usr/bin", "../")
	INTEGER,        // Integer literals (e.g., "123")
	OPTION,         // Command options (e.g., "-l", "-a")
	REDIRECT_IN,    // Input redirection ("<")
	REDIRECT_OUT,   // Output redirection (">")
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
	UNKNOWN         // Any unrecognized or invalid token
} t_token_type;

typedef struct s_slice
{
	char *start; //Pointer to the start of the lexeme. (For 'echo' start is pointing to the 'e')
	size_t length; //Lexeme length.
} t_slice;

typedef struct s_token
{
	t_token_type type;
	//char lexeme; //this needs to be an slice. To hold more than a char.
	t_slice slice;
} t_token;

#endif


