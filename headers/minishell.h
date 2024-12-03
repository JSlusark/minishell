/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:17:33 by alramire          #+#    #+#             */
/*   Updated: 2024/12/03 21:22:48 by jslusark         ###   ########.fr       */
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
#include	"stdbool.h" // ADDED THIS TO HANDLE TRUE / FALSE SITUATIONS - instead than using 0 or 1 (we can use it, yeah?)

// CALL VALGRIND SUPPRESSION:
// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

// ANSI color codes (added them just to test for now, we shouldn't lose time with making it pretty)
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET  "\x1b[0m"

// Tokenizer headers // <---- do you think we can regroup all in one header file? It will simplify things once our project grows
#include "char_itr.h"
#include "guards.h"
#include "scanner.h"
#include "cmd.h"
#include "token_list.h"
#include "token.h"

// Parsing headers
#include	"node.h" // node structs and node handling functions

//Execution headers
#include	"built_in.h" // this already should include all the builtins headers inside
#include	"env_var.h" // this already should include all the env_var headers inside
#include	"pipes.h" // this already should include all the pipes headers inside
#include	"redirections.h" // this already should include all the redirections headers inside



#endif
