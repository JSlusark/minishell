/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mock_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:13:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 22:27:55 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
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

		// Set the token type and value based on the word
		if (strcmp(word, "echo") == 0) {
			new_token->mock_type = COMMAND;
		} else if (strcmp(word, "|") == 0) {
			new_token->mock_type = PIPE;
		} else {
			new_token->mock_type = STRING_LITERAL;
		}
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
