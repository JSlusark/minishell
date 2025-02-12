/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:17:33 by alramire          #+#    #+#             */
/*   Updated: 2025/02/12 12:44:45 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "../lib/dprintf/ft_dprintf.h"
# include "stdbool.h"
# include <errno.h>
# include <sys/stat.h>
# include "./parsing.h"
# include "./execution.h"

// ANSI color codes
# define COLOR_GREEN  "\x1b[32m"
# define COLOR_RED    "\x1b[31m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_CYAN   "\x1b[36m"
# define COLOR_ORANGE "\x1b[38;5;208m"
# define COLOR_RESET  "\x1b[0m"

#endif
