/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:17:33 by alramire          #+#    #+#             */
/*   Updated: 2024/12/09 15:17:34 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<readline/readline.h>
#include	<readline/history.h>
#include	"../libft/libft.h"
#include	"stdbool.h"

// CALL VALGRIND SUPPRESSION:
// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

// ANSI color codes (added them just to test for now, we shouldn't lose time with making it pretty)
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET  "\x1b[0m"

// Parsing headers
#include	"./parsing/tokens/tokens.h"
#include	"./parsing/nodes/nodes.h" // node structs and node handling functions


//Execution headers



#endif
