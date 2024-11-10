/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:17:33 by alramire          #+#    #+#             */
/*   Updated: 2024/11/10 16:37:44 by jslusark         ###   ########.fr       */
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


// PARSING STRUCTS
#include	"tree_struct.h"
#include	"token.h"
#include	"node.h"
#include	"scanner.h"


// CALL VALGRIND SUPPRESSION:
// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

#endif


