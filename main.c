/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/03 18:13:13 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int argc, char **argv)
{
	char *input;
	t_token_list *tokens;
	t_node_list		*node_list;
	(void)argc; // this silences compilation warnings when we do not use argc
	(void)argv; // this silences compilation warnings when we do not use argv

	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (strlen(input) > 0) // <------------------------------- if the len of the input is more than 0 we have to tokenize, if it's not, we reprompt the user
		{
			/* ALL OUR LOGIC FOR TOKENIZING AND PARSING SHOULD GO DOWN HERE: */
			add_history(input); // <---- THIS WORKS CORRECTLY HERE
			tokens = create_mock_tokens(input); // <-------------- this needs to be substituted by Alejo's token list
			if(!tokens) // if tokenizing fails, free the input and tokenlist
			{
				free(input);
				free_mock_tokens(tokens);
			}
			else // if tokenizing succeeds proceed with creating node list
			{
				node_list = return_nodes(tokens);
				free_mock_tokens(tokens); // we free the token list since we allocated and created our nodes
				free(input); // we also free the input as we have processed it already as tokens and then nodes
				if(!node_list) // error handling
				{
					free_node_list(node_list); // for now this is seen as double free because I al already freeing in every scenario i find in my parsing function
					// after this fails if we write "echo $?" it should print 2
					// so after we free node list we could set $? to 2, not sure how yet or if we can find a better way
				}
				else // success and execute
				{
					print_nodes(node_list); // let's leave this function for error handling, we can comment it our or remove it once we submit the project
					exec_node(node_list); // I already set a simple ground for initiating execution from our nodes
					free_node_list(node_list);// we have to free the node_list when finished executing it and ready to prompt a new input
				}
			}
		}
	}
	clear_history();
	return 0;
}
