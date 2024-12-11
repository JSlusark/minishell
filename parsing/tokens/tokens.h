#ifndef TOKEN_H
#define TOKEN_H

typedef enum e_token_type // good to have an order like below
{
	BUILT_IN,        		// REMOVE (NQ_ARG)
	ENV_VAR,        		// REMOVE (NQ_ARG)
	ABS_PATH,           	// REMOVE (NQ_ARG)
	REL_PATH,           	// REMOVE (NQ_ARG)

	OPTION,         		// REMOVE (ASSIGN ITS TYPE AFTER TOKENIZATION as "-n" or -"n" is still valid)
	REDIR_IN,       		// 5 Input redirection ("<")
	REDIR_OUT,      		// 6 Output redirection (">")
	APPEND_OUT,     		// 7 Append redirection (">>")
	HEREDOC,        		// 8 Here-document redirection ("<<")
	PIPE,           		// 9 Pipe operator ("|")
	ARG,         			//  CAL IT NQ_ARG? 12 Any letter or number that is not surrounded in " " and '', after we create the tokens and nodes, we need a function that will see if the word is an external command or just a word
	DQ_ARG,        // CALL IT DQ_ARG? 10 Strings inside double quotes (e.g., "hello world"), after the string is ready we have to add a function that will see if we have $var inside here because it can be expanded inside double quotes only, we should also have a function that cheks if there is a command token type only inside
	SQ_ARG,        // CALL IT SQ_ARG String inside single quotes (e.g., "hello world"), after the string is ready we should have a function that cheks if there is a command token type only inside

	UNKNOWN,         		//DO NOT NEED
	// I DON'T THINK WE NEED THESE ESPECIALLY BECAUSE THESE DETAILS ARE PART OF THE INVALID TOKENS CATEGORY OR THINGS WE WILL CHECK AFTER WE PARSE TOKENS TO NODES
	// D_STR,         	// we can handle unclosed quotes as an unknown token, we can tokenize closed double quotes strings as STRING_D_QUOTES
	// S_STR,         	// we can handle unclosed quotes as an unknown token, we can tokenize closed double quotes strings as STRING_D_QUOTES
	//EXTERNAL_COMMAND      // commands like grp or ls that we do not have to create, we can access these as binaries in /bin or /usr/bin, we do not need to create tokens for these, after we create our tokens and nodes we will then see if word is a external command
	// DELIMITER,      		// we don't hav  to handle ; as a delimiter as it is required by the bonus, the symbol ; be seen as error if not inside a string
	// OPERATOR,       		// we don't hav  to handle logical operators for `&&` and `||` as they are required by the bonus, these symbols will be seen as an error if not inside a string
	// FILENAME,       		// i don't think we need this as we will check if something is a file based on the commands we find in our nodes
	// SUBSHELL,       		// we do not need to handle subshell
	// COMMENT,        		// we do not need to handle comments
	// PATH_EXP,			// we do not need this
} t_token_type;

typedef struct s_tokens
{
	char *value;
	t_token_type type;
	struct s_tokens *next;
} t_tokens;

t_tokens *return_tokens(char *input);

#endif
