/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroramirez <alejandroramirez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/17 10:10:28 by alejandrora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
//#include "include/node.h"
//#include "include/parser.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_char_itr itr;
	t_scanner scanner;
	//int i;

	printf("ARGC: %d, ARGV:%s\n", argc, argv[0]); // added this just to avoid compilation error
	while (1)
	{
		input = readline("Minishell> "); // suppression file (.supp) is needed to suppress readline leaks

		if (!input || ft_strncmp(input, "exit", 4) == 0)
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
		while (scanner_has_next(&scanner))
		{
			scanner.next = scanner_next(&scanner);
			print_token(scanner.next);
		}
		print_token(scanner.next); //This is printing the END token
		free(input);
	}
	clear_history(); //Before I had this: rl_clear_history(); shouldn't this run in the while loop? (outside if statements)
	return (0);
}
