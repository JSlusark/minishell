/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 13:31:31 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node_list	*parse(char *input, t_node_list *nodes, t_msh *msh)
{
	t_tokens	*tokens;
	tokens = return_tokens(input);
	if(!tokens)
	{
		free(input);
		free_tokens(tokens);
		printf("- TOKEN FAILED TO ALLOCATE - add error code 2 to $?\n");
	}
	else // if tokenizing succeeds create execution nodes from tokens
	{
		// print_tokens(tokens); // for tokenization error handling
		nodes = return_nodes(tokens, msh);
		free_tokens(tokens);
		free(input);
		if(!nodes) // if parsing has error it returns null and frees everything
		{
			printf("- NODE FAILED TO ALLOCATE - add error code 2 to $?\n");
		}
	}
	return(nodes);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_node_list		*nodes; // previously i assigned NULL to nodes probably for an allocation problem - check later
	t_msh			*msh;
	(void)argc;
	(void)argv;

	msh = NULL;
	ms_env_init(&msh, envp);
	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);
		// should we put a guard where is strlen of input is longer than INTMAX it gives error and reprompts user?
		if (!input) // Handle EOF (Ctrl+D)
		{
			printf("exit\n");
			break;
		}
		if (input && *input) // <---- if the len of the input is more than 0 we have to parse and exec, if it's not, we reprompt the user
		{
			add_history(input);
			nodes = parse(input, nodes, msh);
			if(nodes)
			{
				print_nodes(nodes); // to print on terminal
				// print_nodes_in_outfile(nodes); // <--- X STEFANO: puoi controllare dprintf? perche' non stampa gli args con echo e se gli args sono piu' di uno va in seg fault - la logica e' uguale al printnodes del terminale che non da questi problemi
				exec_nodes(nodes); // <-------- we traverse the node list and execute
				free_node_list(nodes);// after we execute the input we free the nodes
			}
		}
	}
	free(msh); // jess -> just in case, check if this is enough for freeing
	clear_history();
	return 0;
}
