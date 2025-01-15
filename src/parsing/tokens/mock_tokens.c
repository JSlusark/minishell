/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:13:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/13 16:54:13 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
When merging and adding your tokeinzation files here, do not delete this file yet, just remove it from
the compilation process. There may be a chance for this file to be still helpful while we grow and
improve the lexical analysis and tokenization part of the project
*/

#include "../../../include/minishell.h"

// Splits the input into words and assigns enum types
t_tokens *create_mock_tokens(char *input)
{
	char *word;
	t_tokens *head = NULL;      // Head of the linked list
	t_tokens *current = NULL;   // Current node in the linked list

	// Tokenize input based on spaces
	word = strtok(input, " ");
	while (word != NULL) {
		// Allocate memory for a new node
		t_tokens *new_token = malloc(sizeof(t_tokens));
		if (!new_token) {
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		else if (strcmp(word, "|") == 0)
			new_token->type = PIPE; // PIPE (when outside quotes)
		else if (strcmp(word, "&&") == 0
				|| strcmp(word, "||") == 0
				|| word[0] == '\\' // checks 1 backslash not 2
				|| word[0] == ';'
				|| word[0] == '('
				|| word[0] == ')'
				|| word[0] == '#'
				|| word[0] == '&'
				|| word[0] == '`'
				|| word[0] == '*'
				|| word[0] == '~'
				)
			new_token->type = UNKNOWN; // THESE SYMBOLS IF USED OUTSIDE QUOTES SHOULD NOT BE PROCESSED
		else if (strcmp(word, "<") == 0)
			new_token->type = REDIR_IN; // REDIR_IN (when outside quotes)
		else if (strcmp(word, ">") == 0)
			new_token->type = REDIR_OUT; // REDIR_OUT (when outside quotes)
		else if (strcmp(word, ">>") == 0)
			new_token->type = APPEND; // APPEND (when outside quotes)
		else if (strcmp(word, "<<") == 0)
			new_token->type = HEREDOC; // HEREDOC (when outside quotes)
		else if (word[0] == '$')
			new_token->type = ENV_VAR; // $environment variable (when outside quotes)
		else if (word[0] == '/')
			new_token->type = ABS_PATH; // ABSOLUTE PATH
		else if (strstr(word, "./") == word || strstr(word, "../") == word)
			new_token->type = REL_PATH; // RELATIVE PATH
		else if (word[0] == '-')
			new_token->type = OPTION; // OPTION <- i don't know if we need this
		else
			new_token->type = ARG; // any thing else
		// Set the value and initialize the next pointer
		new_token->value = strdup(word); // Duplicate the word for storage
		new_token->next = NULL;
		// Add the new token to the linked list
		if (!head) {
			head = new_token;  // First token becomes the head
		} else {
			current->next = new_token; // Link the new token
		}
		current = new_token;  // Move to the new end of the list

		// Get the next word
		word = strtok(NULL, " ");
	}

	return head; // Return the head of the linked list
}
