/*
STRUCTS ARE AT END OF FILE.

THOUGHT PROCESS:
1. Collect all argvs from main into a collector variable;
2. Split the text from the collector and create a char **token_array
3. Go through each char* from the char **token_array and initiate nodes in t_tree struct that collects info on each token that can be used for parsing, expansion and execution


EXAMPLE FUNCTION TO INITIATE TREE:
t_tree *parse_tokens(char **token_array)
{
    t_tree *head = NULL, *current = NULL;

    for (int i = 0; token_array[i] != NULL; i++) {
        t_tree *new_node = malloc(sizeof(t_tree));
        new_node->token = strdup(token_array[i]);
        new_node->type = determine_token_type(token_array[i]); // Define this function
        new_node->related_tokens = NULL; // Attach related commands if needed
        new_node->next = NULL;

        if (current == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            new_node->prev = current;
            current = new_node;
        }
    }
    return head;
}


 EXAMPLE FUNCTION TO ASSIGN TOKEN TYPE TO EVERY TOKEN/NODE:
t_token_type determine_token_type(char *token)
{
    if (is_command(token)) return COMMAND;
    if (is_path(token)) return PATH;
    if (is_integer(token)) return INTEGER;
    if (is_option(token)) return OPTION;
    if (strcmp(token, "<") == 0) return REDIRECT_IN;
    if (strcmp(token, ">") == 0) return REDIRECT_OUT;
    if (strcmp(token, ">>") == 0) return APPEND_OUT;
    if (strcmp(token, "<<") == 0) return HEREDOC;
    if (strcmp(token, "|") == 0) return PIPE;
    if (is_env_var(token)) return ENV_VAR;
    if (is_subshell(token)) return SUBSHELL;
    if (is_string_literal(token)) return STRING_LITERAL;
    if (is_builtin(token)) return BUILTIN;
    if (strcmp(token, "&&") == 0) return LOGICAL_AND;
    if (strcmp(token, "||") == 0) return LOGICAL_OR;
    if (strcmp(token, ";") == 0) return SEMICOLON;

    return UNKNOWN;
}

*/


typedef enum e_token_type // check how many times we actually need
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
	SUBSHELL,       // Subshell commands or groupings (e.g., "(command)")
	STRING_LITERAL, // String literals in quotes (e.g., "hello world")
	BUILTIN,        // Built-in shell commands (e.g., "exit", "pwd", "export")
	LOGICAL_AND,    // Logical AND ("&&")
	LOGICAL_OR,     // Logical OR ("||")
	SEMICOLON,      // Command separator (";")
	UNKNOWN         // Any unrecognized or invalid token
} t_token_type;


typedef struct s_tree
{
	struct s_tree *prev;
	char *token;         // The actual token string (e.g., "cd", "..", etc.)
	t_token_type type;   // Token type defined by the enum
	// struct s_related *related_tokens; // PROBABLY NOT NEEDED CHECK NOTES ON OBSIDIAN ABOUT IT
	int position;        // Position in the command sequence, useful for certain evaluations
	int tree_len;        // Total length of the command sequence/tree, could be tracked elsewhere too
	struct s_tree *next;
} t_tree;
