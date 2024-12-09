/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:25:21 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/06 13:05:54 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void print_tokens(t_token_list *token)
{
	int token_n = 1; // Token count for display purposes

	printf(COLOR_GREEN"\nPRINTING TOKENS...\n"COLOR_RESET);
	while (token)
	{
		// Print the token number and its value
		printf(COLOR_BLUE"    TOKEN_%d:"COLOR_RESET, token_n);
		printf(" %s ", token->value);

		// Print additional information based on the token type
		if (token->type == PIPE)
			printf(COLOR_YELLOW" <-- Pipe token\n"COLOR_RESET);
		else if (token->type == REDIR_IN)
			printf(COLOR_YELLOW" <-- Redirection input\n"COLOR_RESET);
		else if (token->type == REDIR_OUT)
			printf(COLOR_YELLOW" <-- Redirection output\n"COLOR_RESET);
		else if (token->type == APPEND_OUT)
			printf(COLOR_YELLOW" <-- Append output\n"COLOR_RESET);
		else if (token->type == HEREDOC)
			printf(COLOR_YELLOW" <-- Heredoc redirection\n"COLOR_RESET);
		else if (token->type == OPTION)
			printf(COLOR_YELLOW" <-- Option token (-n, etc.)\n"COLOR_RESET);
		else if (token->type == WORD)
			printf(COLOR_YELLOW" <-- cmd, argument or path/file token\n"COLOR_RESET);
		else
			printf(COLOR_RED" <-- Unknown token\n"COLOR_RESET);

		// Move to the next token
		token = token->next;
		token_n++;
	}
	printf(COLOR_GREEN"\nEND OF TOKENS.\n"COLOR_RESET);
}
