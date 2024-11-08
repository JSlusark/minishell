#include "./include/scanner.h"

t_scanner scanner_value(t_char_itr char_itr)
{}

int scanner_has_next(const t_scanner *self)
{}

t_token scanner_peek(const t_scanner *self)
{}

t_token scanner_next(t_scanner *self)
{}

// This functions returns the tokens.
void parse(t_scanner *scanner)
{
	t_token next = scanner_peek(scanner);
	if (next.type ==  )

}
