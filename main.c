/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/10/30 19:01:26 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	char	*input;

	while (1)
	{
		// Display the shell prompt and wait for user input
		input = readline("Minishell> ");

		// Check for end-of-file (EOF) or "exit" command to terminate
		if (!input || strcmp(input, "exit") == 0) {
			free(input);
			printf("Exiting Minishell...\n");
			exit(0); // Terminate the program immediately
		}
		// Process the input (replace this with actual parsing and execution)
		if (strlen(input) > 0) {
			add_history(input); // Adds to command history
			printf("You entered: %s\n", input); // Placeholder for command processing
		}
		free(input);
	}

	return (0);
}
