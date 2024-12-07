/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/02 19:19:35 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
//#include "include/node.h"
//#include "include/parser.h"

int	main(int argc, char **argv)
{
	char			*input;
	t_token_list	*tokens;
	t_node			*node_list;
	t_char_itr		itr;
	t_scanner		scanner;
	(void)argc; // this silences compilation warnings when we do not use argc
	(void)argv; // this silences compilation warnings when we do not use argv

	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			itr = char_itr_value(input, ft_strlen(input));
			//if(check_start_uknown(itr.cursor)== 1)
			//printf("Minishell: unknown command '%c' \n", itr.cursor[0]);
			scanner = scanner_value(itr);
			tokens = init_token_list(&scanner);
		}
		if(!tokens)
		{
			free(input);
			free_mock_tokens(tokens);
		}
		if(ft_strcmp(input, "exit") == 0) //<---- we will have to remove this as we handle exit in the execution bit
		{
			free(input);
			free_mock_tokens(tokens);
			clear_history();
			exit(0);
		}
		else
		{
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
	}
	clear_history(); //Before I had this: rl_clear_history(); shouldn't this run in the while loop? (outside if statements)
	return (0);
}
