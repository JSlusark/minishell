#include "./include/minishell.h"

int compare_token(const t_token *token, const char *str)
{
	return strncmp(token->lexeme.start, str, token->lexeme.length);
}

void check_cmd(t_scanner *self)
{
	printf("=====check cmd====\n");
	printf("Comparing starting char: %p | char %s\n", self->char_itr.cursor, self->char_itr.cursor);
	printf("Comparing strings: '%.*s' and 'echo'\n", (int)self->next.lexeme.length, self->char_itr.cursor);
	if (compare_token(&self->next, "echo") == 0)
	{
		printf("+++son iguales+++\n");
		printf("self->next.lexeme.length: %zu\n", self->next.lexeme.length);
		self->next.type = COMMAND;
	}
	else
	{
		printf("+++ NONONO son iguales+++\n");
		self->next.type = WORD;
	}
}
