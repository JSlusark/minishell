/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/25 11:46:16 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int argc, char **argv) {
	char *input;

	printf("ARGC: %d, ARGV: %s\n", argc, argv[0]);
	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (strlen(input) > 0)
			add_history(input); // FOUND BUGS HERE
		if(ft_strcmp(input, "exit") == 0)
		{
			free(input);
			clear_history();
			printf("Exiting Minishell..\n");
			exit (0);
		}
		// Creates mock tokens, this will have to be substituted by the token list created from alejo
		t_token_list	*tokens = create_mock_tokens(input);
		//We have our node list! I do not call it AST because AST is a lists of nodes unified by &&, || and ; which is bomus work
		t_node *node_list = parse(tokens);
		free_mock_tokens(tokens); // we free the token list after we used them for the nodes
		free(input);
		if(!node_list)
		{
			printf("Error increating node! (I could possibly return the error here too..?)\n"); // free not needed?
			// actually i can free here at every error returned instead!
		}
		else
		{
			print_nodes(node_list); // i am able to print the nodes data here!
			exec_node(node_list);
			free_node_list(node_list);// we have to free the node_list before we free the input and get more input
		}
	}
	clear_history();
	return 0;
}
