#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "char_itr.h"
#include "token.h"
#include "guards.h"

typedef struct s_token_list
{
	t_token_type type;         // just type,  Type of the token, e.g., COMMAND, STRING_LITERAL, etc.
	char *value;      // just value, Value of the token, e.g., "echo", "hello"
	struct s_token_list *next; // Just next, Pointer to the next token in the linked list
} t_token_list;


t_token_list *init_token_list(t_scanner *self);

/*

This was the original token list used by Jess.

typedef struct s_mock
{
	int mock_type;         // Type of the token, e.g., COMMAND, STRING_LITERAL, etc.
	char *mock_value;      // Value of the token, e.g., "echo", "hello"
	struct s_mock *next; // Pointer to the next token in the linked list
}			t_mock;
 */
#endif
