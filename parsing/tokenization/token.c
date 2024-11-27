#include "../../headers/minishell.h"


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
	printf("[Token Type]: %d\n", token.type);
	printf("[Token Lexeme]: %.*s\n", (int)token.lexeme.length, token.lexeme.start);
}

t_token end_token (t_scanner *self)
{
	self->next.type = END;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	return (self->next);
}

t_token pipe_token (t_scanner *self)
{
	self->next.type = PIPE;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	self->char_itr.cursor++;
	return (self->next);
}

t_token redir_out_token (t_scanner *self)
{
	self->next.type = REDIR_OUT;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	self->char_itr.cursor++;
	return (self->next);
}

t_token redir_in_token (t_scanner *self)
{
	self->next.type = REDIR_IN;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	self->char_itr.cursor++;
	return (self->next);
}

t_token word_token (t_scanner *self)
{
	self->next.lexeme.start = self->char_itr.cursor;

	while(self->char_itr.cursor && ft_isalnum(*self->char_itr.cursor))
	{
		self->next.lexeme.length++;
		//printf("self->next.lexeme.length: %zu\n", self->next.lexeme.length);
		self->char_itr.cursor++;
	}
	check_cmd(self);
	return (self->next);
}

t_token tmp_unknown_token (t_scanner *self)
{
	self->next.type = UNKNOWN;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	self->char_itr.cursor++;
	return (self->next);
}
