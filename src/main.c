/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/23 17:29:30 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node_list	*parse(char *input, t_node_list *nodes, t_msh *msh)
{
	t_tokens	*tokens;
	tokens = return_tokens(input, msh);
	if(!tokens)
	{
		// print_tokens(tokens); // for tokenization error handling
		if(input)
			free(input);
		if (tokens)
			free_tokens(tokens); // need to better check this when hitting error as it did not work for invalid tokens
		nodes = NULL;
	}
	else // if tokenizing succeeds create execution nodes from tokens
	{
		print_tokens(tokens); // for tokenization error handling
		nodes = return_nodes(tokens, msh);
		if(tokens)
			free_tokens(tokens);
		if(input)
			free(input);
	// if(!nodes) // if parsing has error it returns null and frees everything
		return(NULL); // using this without if just to test tokens
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
				// print_nodes_in_outfile(nodes);
				exec_nodes(nodes);
				free_node_list(nodes);// after we execute the input we free the nodes )
			}
		}
	}
	free_msh(msh); // <------ from JESS: ho cambiato free(msh) in free_msh(msh) per libreare anche cioe' che e' all'interno della struttura (non in che casi questa funzione cerra' chiamata in questo punto, l'ho messa anche in cmd exit prima di liberare la node list)
	clear_history();
	return 0;
}
