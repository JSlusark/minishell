#include "./include/token.h"
#include "./include/minishell.h"

t_token new_token (t_token_type type, char *start, size_t length)
{
	t_token token;

	token.type = type;
	token.lexeme.length = length;
	token.lexeme.start = start;

	return (token);
}

void print_token(const t_token token)
{
	//print all token data
	printf("Token Type: %d\n", token.type);
	printf("Token Lexeme: %.*s\n", (int)token.lexeme.length, token.lexeme.start);
}
