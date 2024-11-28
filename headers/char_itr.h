/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_itr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:33:18 by alramire          #+#    #+#             */
/*   Updated: 2024/11/28 12:42:18 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_ITR_H
#define CHAR_ITR_H


#define WHITESPACES " \t\r\n\a\"" //Space, tab, carriage return, newline, bell, double quote.
#define SYMBOLS "\\;()#&`*~/|"

typedef struct s_chart_itr
{
	const char *cursor; //Holds the current position of the string
	const char *sentinel1; //The end position of the string
} t_char_itr;

// value lifetime dependes of the start reference
t_char_itr char_itr_value(const char *star, size_t length);

//Returns pointer to the current location of iterator cursor porinter.
const char* char_itr_cursor(const t_char_itr *self);

//Returns true when there are aditional chars to consume on the iterable range
int char_itr_has_next(const t_char_itr *self);

//peek and return the next character. Do not advance the cursor. Will crash out of bound if no more chars to consume
char char_itr_peek(const t_char_itr *self);

//read next char and advance cursor. Will crash out of bound if no more chars to consume
char char_itr_next(t_char_itr *self);

//Function to skip whitespaces
void skip_whitespaces (t_char_itr *self);

//Function to know if there is a whitespace
int is_whitesace(t_char_itr *self);

#endif
