/*

Provides an interator to traverse a string character by character


 */

#ifndef CHAR_ITR_H
#define CHAR_ITR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_chart_itr
{
	const char *cursor; //Holds the current position of the string
	const char *sentinel1; //The end position of the string
} t_char_itr;

// value lifetime dependes of the start reference
t_char_itr chart_itr_value(const char *star, size_t length);

//Returns pointer to the current location of iterator cursor porinter.
const char* char_itr_cursor(const t_char_itr *self);

//Returns true when there are aditional chars to consume on the iterable range, there are more chars to read
int chart_itr_has_next(const t_char_itr *self);

//peek and return the next character. Do not advance the cursor. Will crash out of bound if no more chars to consume
char char_itr_peek(const t_char_itr *self);

//read next char and advance cursor. Will crash out of bound if no more chars to consume
char char_itr_next(t_char_itr *self);

#endif
