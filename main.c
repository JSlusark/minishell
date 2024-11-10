/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 16:10:58 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
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
		if (ft_strncmp(input, "echo ", 5) == 0)
		{
			printf("%s\n", input + 5);
		}
		free(input);
	}
	rl_clear_history(); // shouldn't this run in the while loop? (outside if statements)
	return (0);
}
