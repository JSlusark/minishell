/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:24:59 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/20 13:15:50 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


char *return_enum(int token_type)
{
	if (token_type == REDIR_IN)
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
	else if (token_type == INVALID)
		return "REDIR_IN (<)"; // Input redirection ("<")
	else
		return "UNRECOGNISED ENUM"; // For invalid enum values
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
