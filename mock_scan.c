/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_scan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:09:12 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 16:09:21 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"  // Your header file with `t_node`, `t_command_node`, etc.

typedef struct s_mock_scanner {
	t_token *tokens;
	int index;
	int length;
} t_mock_scanner;

// Initializes a mock scanner with a predefined list of tokens
t_mock_scanner *mock_scanner_init(t_token *tokens, int length) {
	t_mock_scanner *mock = malloc(sizeof(t_mock_scanner));
	mock->tokens = tokens;
	mock->index = 0;
	mock->length = length;
	return mock;
}

// Checks if there are more tokens in the mock scanner
int mock_scanner_has_next(const t_mock_scanner *mock) {
	return mock->index < mock->length;
}

// Peeks at the current token without advancing the index
t_token mock_scanner_peek(const t_mock_scanner *mock) {
	return mock->tokens[mock->index];
}

// Gets the current token and advances the index
t_token mock_scanner_next(t_mock_scanner *mock) {
	return mock->tokens[mock->index++];
}
