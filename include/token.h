#ifndef TOKEN_H
#define TOKEN_H

typedef enum e_token_type // good to have an order like below
{
	COMMAND,        // Shell commands (e.g., "cd", "echo", "ls")
	BUILTIN,        // Built-in shell commands (e.g., "exit", "pwd", "export")
	ENV_VAR,        // Environment variable (e.g., "$HOME", "$USER")
	PATH,           // Path values (e.g., "/usr/bin", "../")
	OPTION,         // Command options (e.g., "-l", "-a")

	REDIR_IN,       // Input redirection ("<")
	REDIR_OUT,      // Output redirection (">")
	APPEND_OUT,     // Append redirection (">>")
	HEREDOC,        // Here-document redirection ("<<")

	PIPE,           // Pipe operator ("|")
	STRING,         // String literals in quotes (e.g., "hello world")
	DELIMITER,      // Command separators (e.g., ";")

	FILENAME,           // File arguments (e.g., "output.txt" in `echo hello > output.txt`)

	OPERATOR,       // Logical operators for `&&` and `||` (used in bonus part only)

	// Additional useful types for completeness
	SUBSHELL,       // Subshell groupings like `(command)`
	COMMENT,        // Comments (usually `#` followed by text)
	UNKNOWN         // Any unrecognized or invalid token type
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

#endif


