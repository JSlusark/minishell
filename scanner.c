#include "./include/scanner.h"

/*
We need to initialize the first scanner structure with its
iterator located at the first token and the first token.
*/
t_scanner scanner_value(t_char_itr char_itr)
{
	t_scanner scanner;
	t_token next; // we really need to have the token in the t_scanner struct?

	whitespaces(&char_itr);
	next = scanner_next(&char_itr);
	scanner.char_itr = char_itr;
	scanner.next = next;
	return(scanner);
}

int scanner_has_next(const t_scanner *self)
{
	char c;
	c = char_itr_peek(&self->char_itr);
	if(c == EOF || c == '\n' || c == '\0')
		return (0)
	else
		return (1);

	//This should be something like, if there is something after token slice?


}

t_token scanner_peek(const t_scanner *self)
{}

t_token scanner_next(t_scanner *self)
{
	whitespaces(&self->char_itr);
}

// This functions returns the tokens. Not sure...
void parse(t_scanner *scanner)
{
	t_token next = scanner_peek(scanner);
	if (next.type ==  )

}
