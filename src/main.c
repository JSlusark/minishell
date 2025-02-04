/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/04 19:44:38 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

t_node_list	*parse(char *input, t_node_list *nodes, t_msh *msh)
{
	t_tokens	*tokens;
	tokens = return_tokens(input, msh);
	if(!tokens)
	{
		// print_tokens(tokens); // for tokenization error handling
		msh->prev_exit = msh->exit_code;  /// <---------------------------------------IMPORTANT TO PRINT CORRECT EXIT CODE
		if(input)
			free(input);
		if (tokens)
			free_tokens(tokens); // need to better check this when hitting error as it did not work for invalid tokens
		nodes = NULL;
	}
	else // if tokenizing succeeds create execution nodes from tokens
	{
		// if(tokens)
			// print_tokens(tokens); // for tokenization error handling
		nodes = return_nodes(tokens, msh);
		if(tokens)
			free_tokens(tokens);
		if(input)
			free(input);
	if(!nodes) // if parsing has error it returns null and frees everything
		{
			msh->prev_exit = msh->exit_code;  /// <---------------------------------------IMPORTANT TO PRINT CORRECT EXIT CODE
			return(NULL); // using this without if just to test tokens}
		}
	}
	return(nodes);
}

static void	check_signals(t_msh *msh)
{
	if (g_sig == SIGINT)
	{
		msh->prev_exit = 130;
		g_sig = 0;
		// printf("SIGINT 2 exit code %d\n", msh->prev_exit);
	}
	if (g_sig == SIGQUIT)
	{
		// msh->prev_exit = 130
		// printf("SIGQUIT 3 exit code %d\n", msh->prev_exit);
		g_sig = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_node_list		*nodes; // previously i assigned NULL to nodes probably for an allocation problem - check later
	t_msh			*msh;
	(void)argc;
	(void)argv;

	setup_signals();
	msh = NULL;
	// ft_dprintf("***-----NEW LOG---------***\n");
	ms_env_init(&msh, envp);
	while (1)
	{
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET); // <------- DA JESS: input originale, usare questo ci fa passare 102 test
		// input = read_input(); ///<----- DA JESS: non ci fa passare due test (non so ancora quali, ci fa passare 100 test)
		// should we put a guard where is strlen of input is longer than INTMAX it gives error and reprompts user?
		if (!input) // Handle EOF (Ctrl+D)
			handle_eof(msh);
		else if (input && *input) // <---- if the len of the input is more than 0 we have to parse and exec, if it's not, we reprompt the user
		{
			check_signals(msh);
			add_history(input);
			nodes = parse(input, nodes, msh);
			if(nodes)
			{
				// print_nodes(nodes); // to print on terminal
				// print_nodes_file(nodes);
				exec_nodes(nodes);
				// msh->prev_exit = msh->exit_code;  /// <---------------------------------------IMPORTANT TO PRINT CORRECT EXIT CODE
				free_node_list(nodes);// after we execute the input we free the nodes )
			}
			// printf("END INPUT exit code %d\n", msh->exit_code);
			msh->prev_exit = msh->exit_code;  /// <---------------------------------------IMPORTANT TO PRINT CORRECT EXIT CODE
		}
	}
	free_msh(msh); // <------ from JESS: ho cambiato free(msh) in free_msh(msh) per libreare anche cioe' che e' all'interno della struttura (non in che casi questa funzione cerra' chiamata in questo punto, l'ho messa anche in cmd exit prima di liberare la node list)
	clear_history();
	return 0;
}

