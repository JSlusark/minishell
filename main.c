/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/27 12:37:51 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
//#include "include/node.h"
//#include "include/parser.h"

int	main(int argc, char **argv)
{
	char			*input;
	t_char_itr		itr;
	t_scanner		scanner;
	t_token_list	*tokens;
	t_node			*node_list;

	printf("ARGC: %d, ARGV:%s\n", argc, argv[0]); // added this just to avoid compilation error
	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		itr = char_itr_value(input, ft_strlen(input));
		scanner = scanner_value(itr);
		tokens = init_token_list(&scanner);
		if(!tokens)
		{
			free(input);
			free_mock_tokens(tokens);
		}
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_mock_tokens(tokens);
			clear_history();
			exit (0);
		}
		else
		{
			if (ft_strlen(input) > 0)
				add_history(input); // NOTE FOR LATER - FOUND BUGS WHEN NAVIGATING THROUGH HISTORY
			node_list = return_nodelist(tokens); //
			free_mock_tokens(tokens); // we free the token list since we allocated and created our nodes
			free(input); // we also free the input as we have processed it already as tokens and then nodes
			if(!node_list)
			{
				// planning that every error (not only allocation error but also parsing error) makes the parsing list "NULL"
				// so that we just need to free once in here and not on every parsing considion with meet
				// could also return an error, but need to check
				// printf("Error increating node! (I could possibly return the error here too..?)\n"); // prob will print in the fuction, i will just free here
				free_node_list(node_list); // for now this is seen as double free because I al already freeing in every scenario i find in my parsing function
			}
			else
			{
				// print node logic will be added here just to help us with error handling, we can comment it our or remove it once we submit the project
				print_nodes(node_list); // let's leave this function for error handling, we can comment it our or remove it once we submit the project
				exec_node(node_list); // I already set a simple ground for initiating execution from our nodes
				free_node_list(node_list);// we have to free the node_list when finished executing it and ready to prompt a new input
			}
		}
/*
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			printf("You entered: %s\n", input); // Placeholder for command processing
		}
		// The itr struct is initialized with the input and the length of it.
		itr = char_itr_value(input, ft_strlen(input));
		scanner = scanner_value(itr);
		init_token_list(&scanner);
/* 		while (scanner_has_next(&scanner))
		{
			scanner.next = scanner_next(&scanner);
			print_token(scanner.next);
		} */
		//print_token(scanner.next); //This is printing the END token
	}
	clear_history(); //Before I had this: rl_clear_history(); shouldn't this run in the while loop? (outside if statements)
	return (0);
}
