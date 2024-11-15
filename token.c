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
	return (self->next);
}

t_token redir_out_token (t_scanner *self)
{
	self->next.type = REDIR_OUT;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	return (self->next);
}

t_token redir_in_token (t_scanner *self)
{
	self->next.type = REDIR_IN;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	return (self->next);
}

t_token word_token (t_scanner *self)
{
	self->next.lexeme.start = self->char_itr.cursor;
	while(self->char_itr.cursor && ft_isalnum(*self->char_itr.cursor))
	{
		self->next.lexeme.length++;
		self->char_itr.cursor++; //There is any difference between advancing with char_itr_next() vs this way?
	}
	self->next.type = WORD;
	//self->next.lexeme.length = 1; //Is already defined in the while
	return (self->next);
}

t_token unknown_token (t_scanner *self)
{
	self->next.type = UNKNOWN;
	self->next.lexeme.length = 1;
	self->next.lexeme.start = self->char_itr.cursor;
	return (self->next);
}
