/*

Defines the types of tokens and the structure of a token used in the shell
The scanner is like an interator
Char itr is producing a char at a time, the scanner is producing a token at a time


 */

#ifndef TOKEN_ITR_H
#define TOKEN_ITR_H

#include "char_itr.h"
#include "token.h"




typedef struct s_scanner
{
	t_char_itr char_itr;
	//char next; //In real scanner this will be a token... like the next token?
	t_token next; // Like this one?
} t_scanner;

//Initializes the scanner witha a character iterator.
t_scanner scanner_value(t_char_itr char_itr);

//Check if there are more tokens to produce.
int scanner_has_next(const t_scanner *self);

//Returns the next token without advancing the scanner
//When is needed to look at the next token to make a decision but do not want to move the scanner forward.
//Example, checking if the next token is a specific type (command or operator) before deciding how to parse or process it.
t_token scanner_peek(const t_scanner *self);

//Returns the next token and advances the scanner.
//When ready to consume and advance the next token in the sequence
t_token scanner_next(t_scanner *self);

#endif
