#ifndef TOKEN_H
#define TOKEN_H

typedef enum e_token_type // good to have an order like below
{
	BUILT_IN,        		// 0 These are the commands we need to create ("echo, cd, pwd, export, unset, env, exit")
	ENV_VAR,        		// 1 Environment variable are words that start with $ (e.g., "$HOME", "$USER"), we do error handling for this after the tokenizing and node creation
	ABS_PATH,           	// 2 A path starting with / (e.g., /directory/directory/  or /directory/file ) is an absolute path and refers to the exact location of the file or command file system staring from root directory
	REL_PATH,           	// 3 A path that doesn’t start with ./ or ../ It is relative to the current working directory. (example ./directory/directory/  or ../directory/directory/  or ../directory/directory/ or ../directory/file )
	PATH_EXP,				// 4 Not sure that we have to handle path expansion with "~" but leaving it here for now
	OPTION,         		// 5 Command options (only "-n" with echo) -> probably do not need to tokenize.

	REDIR_IN,       		// 6 Input redirection ("<")
	REDIR_OUT,      		// 7 Output redirection (">")
	APPEND_OUT,     		// 8 Append redirection (">>")
	HEREDOC,        		// 9 Here-document redirection ("<<")

	PIPE,           		// 10 Pipe operator ("|")
	STRING_D_QUOTES,        // 11 Strings inside double quotes (e.g., "hello world"), after the string is ready we have to add a function that will see if we have $var inside here because it can be expanded inside double quotes only, we should also have a function that cheks if there is a command token type only inside
	STRING_S_QUOTES,        // 12 String inside single quotes (e.g., "hello world"), after the string is ready we should have a function that cheks if there is a command token type only inside

	WORD,         			// 13 Any letter or number that is not surrounded in " " and '', after we create the tokens and nodes, we need a function that will see if the word is an external command or just a word
	UNKNOWN,         		// 14 An invalid token type is a symbol that our shell won't have to execute: "\", ";", "&&", "||", unclosed " and ', "(", ")", "#", "&", "$(...)", `backticks, "*" etc.. --- what about tilde?

	// I DON'T THINK WE NEED THESE ESPECIALLY BECAUSE THESE DETAILS ARE PART OF THE INVALID TOKENS CATEGORY OR THINGS WE WILL CHECK AFTER WE PARSE TOKENS TO NODES
	//EXTERNAL_COMMAND      // commands like grp or ls that we do not have to create, we can access these as binaries in /bin or /usr/bin, we do not need to create tokens for these, after we create our tokens and nodes we will then see if word is a external command
	// D_QUOTE,         	// we can handle unclosed quotes as an unknown token, we can tokenize closed double quotes strings as STRING_D_QUOTES
	// S_QUOTE,         	// we can handle unclosed quotes as an unknown token, we can tokenize closed double quotes strings as STRING_D_QUOTES
	// DELIMITER,      		// we don't hav  to handle ; as a delimiter as it is required by the bonus, the symbol ; be seen as error if not inside a string
	// OPERATOR,       		// we don't hav  to handle logical operators for `&&` and `||` as they are required by the bonus, these symbols will be seen as an error if not inside a string
	// FILENAME,       		// i don't think we need this as we will check if something is a file based on the commands we find in our nodes
	// SUBSHELL,       		// we do not need to handle subshell
	// COMMENT,        		// we do not need to handle comments
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


