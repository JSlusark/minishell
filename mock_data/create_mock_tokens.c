/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mock_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:13:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/20 15:28:26 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void free_mock_tokens(t_mock *head) {
	t_mock *current = head;
	t_mock *next;

	while (current != NULL) {
		next = current->next_token; // Store the next token
		free(current->mock_value); // Free the duplicated string
		free(current);             // Free the current node
		current = next;            // Move to the next token
	}
}

// Splits the input into words and assigns enum types
t_mock *create_mock_tokens(char *input)
{
	char *word;
	t_mock *head = NULL;      // Head of the linked list
	t_mock *current = NULL;   // Current node in the linked list

	// Tokenize input based on spaces
	word = strtok(input, " ");
	while (word != NULL) {
		// Allocate memory for a new node
		t_mock *new_token = malloc(sizeof(t_mock));
		if (!new_token) {
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		if (strcmp(word, "exit") == 0
			|| strcmp(word, "unset") == 0
			|| strcmp(word, "cd") == 0
			|| strcmp(word, "pwd") == 0
			|| strcmp(word, "export") == 0
			|| strcmp(word, "echo") == 0
			|| strcmp(word, "cd") == 0
			|| strcmp(word, "env") == 0)
			new_token->mock_type = BUILT_IN; // COMMANDS WE NEED TO CREATE
		else if (strcmp(word, "|") == 0)
			new_token->mock_type = PIPE; // PIPE (when outside quotes)
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
				)
			new_token->mock_type = UNKNOWN; // THESE SYMBOLS IF USED OUTSIDE QUOTES SHOULD NOT BE PROCESSED
		else if (strcmp(word, "<") == 0)
			new_token->mock_type = REDIR_IN; // REDIR_IN (when outside quotes)
		else if (strcmp(word, ">") == 0)
			new_token->mock_type = REDIR_OUT; // REDIR_OUT (when outside quotes)
		else if (strcmp(word, ">>") == 0)
			new_token->mock_type = APPEND_OUT; // APPEND_OUT (when outside quotes)
		else if (strcmp(word, "<<") == 0)
			new_token->mock_type = HEREDOC; // HEREDOC (when outside quotes)
		else if (word[0] == '$')
			new_token->mock_type = ENV_VAR; // $environment variable (when outside quotes)
		else if (word[0] == '/')
			new_token->mock_type = ABS_PATH; // ABSOLUTE PATH
		else if (strstr(word, "./") == word)
			new_token->mock_type = REL_PATH; // RELATIVE PATH
		else if (word[0] == '~')
			new_token->mock_type = PATH_EXP; // PATH EXPANSION <- unsure we need this
		else if (word[0] == '-')
			new_token->mock_type = OPTION; // OPTION <- i don't know if we need this
		else
			new_token->mock_type = WORD; // any thing else
		// Set the value and initialize the next pointer
		new_token->mock_value = strdup(word); // Duplicate the word for storage
		new_token->next_token = NULL;
		// Add the new token to the linked list
		if (!head) {
			head = new_token;  // First token becomes the head
		} else {
			current->next_token = new_token; // Link the new token
		}
		current = new_token;  // Move to the new end of the list

		// Get the next word
		word = strtok(NULL, " ");
	}

	return head; // Return the head of the linked list
}
