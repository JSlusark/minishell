/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 18:05:51 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/char_itr.h"
#include "include/guards.h"
//#include "include/node.h"
//#include "include/parser.h"
#include "include/scanner.h"
#include "include/token.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_char_itr itr;
	t_scanner scanner;
	int i;

	printf("ARGC: %d, ARGV:%s\n", argc, argv[0]); // added this just to avoid compilation error
	while (1)
	{
		input = readline("Minishell> "); // suppression file (.supp) is needed to suppress readline leaks

		if (!input || ft_strncmp(input, "exit", 4) == 0) // THIS DOESNT SEEM TO WORK but should be ok
		{
			free(input);
			printf("Exiting Minishell...\n");
			exit (0); // Terminate the program immediately
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			printf("You entered: %s\n", input); // Placeholder for command processing
		}
		// The itr struct is initialized with the input and the length of it.
		itr = char_itr_value(input, ft_strlen(input));
		scanner = scanner_value(itr);
		// We need to initialize the scanner, with scanner_value(itr);

		printf("Printing pointers input via itr\n");
		printf("Original cursor: %p\n", itr.cursor);
		i = 0;
		//printf("second skip whitespaces\n");
		//skip_whitespaces(&itr);
		while((size_t)i < ft_strlen(input))
		{
			char_itr_cursor (&itr);
			char_itr_has_next(&itr);
			char_itr_peek(&itr);
			char_itr_next(&itr);
			char_itr_cursor (&itr);
			i++;
		}
/* 		if (ft_strncmp(input, "echo ", 5) == 0)
		{
			printf("%s\n", input + 5);
		} */

		free(input);
	}
	rl_clear_history(); // shouldn't this run in the while loop? (outside if statements)
	return (0);
}
