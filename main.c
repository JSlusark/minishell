/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 14:14:51 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int argc, char **argv) {
	char *input;

	printf("ARGC: %d, ARGV: %s\n", argc, argv[0]);
	while (1) {
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (strlen(input) > 0)
		{
			add_history(input);
		}
		if(ft_strcmp(input, "exit") == 0)
		{
			free(input);
			clear_history();
			printf("Exiting Minishell..\n");
			exit (0);
		}
		// Creates mock tokens, this will have to be substituted by the token list created from alejo
		t_mock	*tokens = create_mock_tokens(input);
		//We have our node list! I do not call it AST because AST is a lists of nodes unified by &&, || and ; which is bomus work
		t_node *node_list = parse(tokens);
		free_mock_tokens(tokens); // we free the token list after we used them for the nodes
		print_nodes(node_list); // i am able to print the nodes data here!
		free_node_list(node_list);// we have to free the node_list before we free the input and get more input
		free(input);
	}
	clear_history();
	return 0;
}
