/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mock_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:13:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 16:47:05 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

		// Determine the token type based on the word content
		if (strcmp(word, "echo") == 0 || strcmp(word, "cd") == 0 || strcmp(word, "ls") == 0) {
			new_token->mock_type = COMMAND;
		} else if (strcmp(word, "exit") == 0 || strcmp(word, "pwd") == 0 || strcmp(word, "export") == 0) {
			new_token->mock_type = BUILTIN;
		} else if (strcmp(word, "|") == 0) {
			new_token->mock_type = PIPE;
		} else if (strcmp(word, "&&") == 0 || strcmp(word, "||") == 0) {
			new_token->mock_type = OPERATOR; // Handle for bonus
		} else if (strcmp(word, "<") == 0) {
			new_token->mock_type = REDIR_IN;
		} else if (strcmp(word, ">") == 0) {
			new_token->mock_type = REDIR_OUT;
		} else if (strcmp(word, ">>") == 0) {
			new_token->mock_type = APPEND_OUT;
		} else if (strcmp(word, "<<") == 0) {
			new_token->mock_type = HEREDOC;
		} else if (word[0] == '$') {
			new_token->mock_type = ENV_VAR; // Environment variable
		} else if (word[0] == '/' || strstr(word, "./") == word) {
			new_token->mock_type = PATH; // Path or relative path
		} else if (word[0] == '-') {
			new_token->mock_type = OPTION; // Command option
		} else {
			new_token->mock_type = STRING; // General string or file
		}

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
