/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/12 16:00:50 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char			*input;
	t_tokens	*tokens;
	t_node_list		*node_list;
	(void)argc;
	(void)argv;
	// (void)tokens;

	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (input && *input) // <---- if the len of the input is more than 0 we have to parse and exec, if it's not, we reprompt the user
		{
			add_history(input);
			tokens = return_tokens(input);
			// tokens = create_mock_tokens(input); // <---- change with actual token freeing function
			if(!tokens)
			{
				printf("tokenlist is null (I just print the tokens and still need to allocate the list for parsing)\n"); // added this just to test the real token list
				free(input);
				free_mock_tokens(tokens); // <---- change with actual token freeing function
			}
			else // if tokenizing succeeds proceed with parsing the tokens into a node list
			{
				node_list = return_nodes(tokens);
				free_mock_tokens(tokens);
				free(input);
				if(!node_list) // if parsing has error it returns null and frees everything
				{
					// do not need to free the nodelist as it's null and we do ilaready  in the return_nodes function
					// I think we should use this to create the error code 0 for situation like for situations like echo $?
				}
				else // if parser is successful we execute and free the node list after we executed
				{
					print_nodes(node_list); // let's leave this function for error handling, we can comment it our or remove it once we submit the project
					exec_nodes(node_list); // <-------- we traverse the node list to handle various execution cases based on the data we assigned to our nodes duting the parsing
					free_node_list(node_list);// after we execute the input we free the node
				}
			}
		}
		else
		{
			free(input);// fixed history navigation -> not when adding more input to the history
			input = NULL; // unsure if thsi is needed
		}
	}
	clear_history();
	return 0;
}
