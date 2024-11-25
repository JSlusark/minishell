/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/25 13:32:53 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int argc, char **argv) {
	char *input;

	printf("ARGC: %d, ARGV: %s\n", argc, argv[0]); // added this to avoid compilation blocks as we don't use this yet
	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (strlen(input) > 0)
			add_history(input); // NOTE FOR LATER - FOUND BUGS WHEN NAVIGATING THROUGH HISTORY
		if(ft_strcmp(input, "exit") == 0)
		{
			free(input); // REMEMBER - this will need to also be handled in signal handling
			clear_history();
			printf("Exiting Minishell..\n");//
			exit (0);
		}
		t_token_list	*tokens = create_mock_tokens(input); // <-------------- this needs to be substituted by Alejo's token list
		t_node *node_list = return_nodelist(tokens); //
		free_mock_tokens(tokens); // we free the token list since we allocated and created our nodes
		free(input); // we also free the input as we have processed it already as tokens and then nodes
		if(!node_list)
		{
			// planning that every error (not only allocation error but also parsing error) makes the parsing list "NULL"
			// so that we just need to free once in here and not on every parsing considion with meet
			// could also return an error, but need to check
			printf("Error increating node! (I could possibly return the error here too..?)\n");
			// free_node_list(node_list); // for now this is seen as double free because I al already freeing in every scenario i find in my parsing function
		}
		else
		{
			// print node logic will be added here just to help us with error handling, we can comment it our or remove it once we submit the project
			print_nodes(node_list); // let's leave this function for error handling, we can comment it our or remove it once we submit the project
			exec_node(node_list); // I already set a simple ground for initiating execution from our nodes
			free_node_list(node_list);// we have to free the node_list when finished executing it and ready to prompt a new input
		}
	}
	clear_history();
	return 0;
}