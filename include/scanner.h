#ifndef TOKEN_ITR_H
#define TOKEN_ITR_H

#include "char_itr.h"
#include "token.h"

//The scanner is like an interator
//Char itr is producing a char at a time, the scanner is producing a token at a time



typedef struct s_scanner
{
	t_char_itr char_itr;
	char next; //In real scanner this will be a token... like the next token?
	t_token next; // Like this one?
} t_scanner;

t_scanner scanner_value(t_char_itr char_itr);

int scanner_has_next(const t_scanner *self);

t_token scanner_peek(const t_scanner *self);

t_token scanner_next(t_scanner *self);

#endif
