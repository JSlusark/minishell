/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:41 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/08 15:55:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	//char next; //In real scanner this will be a token... like the next token?
	t_token next; // Like this one?
} t_scanner;

//Initializing the scanner struct.
t_scanner scanner_value(t_char_itr char_itr);

//Returns 1 if there is more tokens to read, and 0 is not.
int scanner_has_next(const t_scanner *self);

//This returns the token without advancind the iterator.
t_token scanner_peek(const t_scanner *self);

//This returns the token advancind the iterator.
t_token scanner_next(t_scanner *self);

// This functions returns the tokens. Not sure about this one.
void parse(t_scanner *scanner);

#endif