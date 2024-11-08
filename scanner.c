#include "./include/scanner.h"

/*
We need to initialize the first scanner structure with its
iterator located at the first token and the first token.
*/
t_scanner scanner_value(t_char_itr char_itr)
{
	t_scanner scanner;
	t_token next;
	// We need to find a way to advance the iterator, skipping whitespaces.
	while(char_itr.cursor == ' ')
		char_itr.cursor += 1;
	next = scanner_next(&char_itr);
	scanner.char_itr = char_itr;
	scanner.next = next;
	return(scanner);
}

int scanner_has_next(const t_scanner *self)
{}

t_token scanner_peek(const t_scanner *self)
{}

t_token scanner_next(t_scanner *self)
{}

// This functions returns the tokens. Not sure...
void parse(t_scanner *scanner)
{
	t_token next = scanner_peek(scanner);
	if (next.type ==  )

}
