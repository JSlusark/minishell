/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 15:39:25 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int argc, char **argv) {
	char *input;

	printf("ARGC: %d, ARGV: %s\n", argc, argv[0]);
	while (1) {
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (!input || strcmp(input, "exit") == 0) {
			free(input);
			printf("Exiting Minishell...\n");
			break;
		}
		if (strlen(input) > 0) {
			add_history(input);
		}
		// Parse and process tokens - temp for now
		parse(create_mock_tokens(input));
		/*
		// THIS SHOULD BE MY FINAL GOAL
		t_node *ast = parse(mock_tokens);
		// You would now have a parse tree in `ast` representing the commands and pipes
		print_ast(ast); // Implement a print function to verify structure (you can create `print_ast` based on your needs)
 		*/
		free(input);
	}
	clear_history();
	return 0;
}
