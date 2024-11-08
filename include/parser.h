#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "scanner.h"

//The scanner produces a stream of token that we can peek ahead by one.
// the return is a pointer to our root node.
t_node parse(t_scanner *scanner);

#endif
