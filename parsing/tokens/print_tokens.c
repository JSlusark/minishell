/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:24:59 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/13 17:07:59 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char *return_enum(int token_type)
{
	if (token_type == ENV_VAR)
		return "ENV_VAR"; // Environment variables starting with $ (e.g., $HOME)
	else if (token_type == ABS_PATH)
		return "ABS_PATH"; // Absolute path starting with /
	else if (token_type == REL_PATH)
		return "REL_PATH"; // Relative path starting with ./ or ../
	else if (token_type == OPTION)
		return "OPTION"; // Options like -n for echo
	else if (token_type == REDIR_IN)
		return "REDIR_IN (<)"; // Input redirection ("<")
	else if (token_type == REDIR_OUT)
		return "REDIR_OUT (>)"; // Output redirection (">")
	else if (token_type == APPEND)
		return "APPEND (>>)"; // Append redirection (">>")
	else if (token_type == HEREDOC)
		return "HEREDOC (<<)"; // Here-document redirection ("<<")
	else if (token_type == PIPE)
		return "PIPE"; // Pipe operator ("|")
	else if (token_type == ARG)
		return "ARG"; // Any letter or number that is not quoted
	else if (token_type == UNKNOWN)
		return "UNKNOWN"; // Invalid token (e.g., \, ;, &&, ||, etc.)
	else
		return "INVALID_ENUM"; // For invalid enum values
}

void print_tokens(t_tokens *tokens)
{
	printf(COLOR_GREEN"TOKEN LIST\n"COLOR_RESET);
    t_tokens *current = tokens; // Start at the head of the token list
    int i = 0;
	while (current != NULL) // Traverse until the end of the list
    {
        printf(COLOR_BLUE"Token %d:"COLOR_RESET, i);
        printf("%s", current->value);
        printf(COLOR_YELLOW"<--- %s\n"COLOR_RESET, return_enum(current->type));
        current = current->next; // Move to the next token
		i++;
    }
}