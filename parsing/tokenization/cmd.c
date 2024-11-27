#include "../../headers/minishell.h"

int compare_token(const t_token *token, const char *str)
{
	//printf("+++Comparing token: '%.*s' with string: '%s'+++\n", (int)token->lexeme.length, token->lexeme.start, str);
	return strncmp(token->lexeme.start, str, token->lexeme.length);
}

void check_cmd(t_scanner *self)
{
	size_t i;

	i = 0;
	//printf("=====check cmd====\n");
	//printf("Comparing starting char: %p | char %c\n", self->char_itr.cursor, *self->char_itr.cursor);
	//printf("Comparing strings: '%.*s' and 'echo'\n", (int)self->next.lexeme.length, self->next.lexeme.start);
	while (i < self->next.lexeme.length)
	{
		//printf("while loop printing\n");
		//printf("Printing: %c\n", self->next.lexeme.start[i]);
		i++;
	}
	if (compare_token(&self->next, "echo") == 0)
	{
		//printf("+++son iguales+++\n");
		//printf("self->next.lexeme.length: %zu\n", self->next.lexeme.length);
		self->next.type = COMMAND;
	}
	else
	{
		//printf("+++ NONONO son iguales+++\n");
		self->next.type = WORD;
	}
}
