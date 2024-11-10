/*
The scanner is where: input lexemes are transformed
into meaningful tokens. Scanner creates meaningful groups of tokens.
clasifying nodes.

*/


#ifndef TOKEN_ITR_H
#define TOKEN_ITR_H

#include "char_itr.h"
#include "token.h"

//The scanner is like an interator
//Char itr is producing a char at a time, the scanner is producing a token at a time



typedef struct s_scanner
{
	t_char_itr char_itr;
	char char_next; //I do not know for what we could use this... but for know let's use it for storing the char when using scanner_next()
	t_token next; // Like this one?
} t_scanner;

//Initializing the scanner struct.
t_scanner scanner_value(t_char_itr char_itr);

//Returns 1 if there is more tokens to read, and 0 is not.
int scanner_has_next(const t_scanner *self);

//This returns the token without advancind the iterator.
t_token scanner_peek(t_scanner *self);

//This returns the token advancing the iterator.
t_token scanner_next(t_scanner *self);

// This functions returns the tokens. Not sure about this one.
void parse(t_scanner *scanner);

#endif
