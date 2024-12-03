/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/03 21:58:58 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	main(int argc, char **argv)
{
	char			*input;
	t_token_list	*tokens;
	t_node_list		*node_list;
	t_char_itr		itr;
	t_scanner		scanner;
	(void)argc; // this silences compilation warnings when we do not use argc
	(void)argv; // this silences compilation warnings when we do not use argv

	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		if (ft_strlen(input) > 0) // <---- if the len of the input is more than 0 we have to tokenize, if it's not, we reprompt the user
		{
			add_history(input);
			itr = char_itr_value(input, ft_strlen(input)); // <--- can we regroup itr, scanner, tokens assignment as one function that does it all and we add it to the main instead?
			//if(check_start_uknown(itr.cursor)== 1)
			//printf("Minishell: unknown command '%c' \n", itr.cursor[0]);
			scanner = scanner_value(itr);
			tokens = init_token_list(&scanner);
			if(!tokens)
			{
				free(input);
				free_mock_tokens(tokens); // <---- need to check if my freeing function works with your tokens too
			}
			else // if tokenizing succeeds proceed with parsing the tokens into a node list
			{
				node_list = return_nodes(tokens);
				free_mock_tokens(tokens);
				free(input);
				if(!node_list) // if parsing has error it returns null and frees everything
				{
					free_node_list(node_list); // for now this is seen as double free because I al already freeing in every scenario i find in my parsing function
					// after this fails if we write "echo $?" it should print 2
					// so after we free node list we could set $? to 2, not sure how yet or if we can find a better way
				}
				else // if parser is successful we execute and free the node list after we executed
				{
					print_nodes(node_list); // let's leave this function for error handling, we can comment it our or remove it once we submit the project
					exec_node(node_list); // <-------- we traverse the node list to handle various execution cases based on the data we assigned to our nodes duting the parsing
					free_node_list(node_list);// after we execute the input we free the node
				}
			}
		}
	}
	clear_history();
	return 0;
}
