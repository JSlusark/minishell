#include "include/char_itr.h"

// value lifetime dependes of the start reference
t_char_itr char_itr_value(const char *star, size_t length)
{
	t_char_itr itr;
	itr.cursor = star;
	itr.sentinel1 = star + length;
	return(itr);
}

//Returns true when there are aditional chars to consume on the iterable range
int chart_itr_has_next(const t_char_itr *self)
{
	return(*self->cursor != '\n' && *self->cursor != '\0');
}
//peek and return the next character. Do not advance the cursor. Will crash out of bound if no more chars to consume
char char_itr_peek(const t_char_itr *self)
{
	return(*self->cursor);
}

//read next char and advance cursor. Will crash out of bound if no more chars to consume
char char_itr_next(t_char_itr *self)
{
	char next;

	next = *self->cursor;
	self->cursor += 1;
	printf("Cursor: %p\n", self->cursor);
	return(next);
}

/* //Returns pointer to the current location of iterator cursor porinter.
const char* char_itr_cursor(const t_char_itr *self)
{

}





*/
