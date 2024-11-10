/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 22:28:44 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int argc, char **argv) {
	char *input;

	printf("ARGC: %d, ARGV: %s\n", argc, argv[0]);
	while (1) {
		input = readline("Minishell> ");
		if (!input || strcmp(input, "exit") == 0) {
			free(input);
			printf("Exiting Minishell...\n");
			break;
		}
		if (strlen(input) > 0) {
			add_history(input);
		}
		// Parse and process tokens
		parse(create_mock_tokens(input));
		free(input);
	}
	clear_history();
	return 0;
}
