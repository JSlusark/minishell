/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:03 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/05 20:10:26 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_sig;

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

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_node_list		*nodes; // previously i assigned NULL to nodes probably for an allocation problem - check later
	t_msh			*msh;
	(void)argc;
	(void)argv;

	ms_env_init(&msh, envp);

	while (1)
	{
		run_signals(1, msh);
		input = readline(COLOR_GREEN "Minishell> " COLOR_RESET);

		if (!input)
			handle_eof(msh);
		else
		{
			if (g_sig == SIGINT) // based on what signal we trigger it will give be a certain exi code
			{
				msh->prev_exit = 130;
				g_sig = 0;
			}
			if (g_sig == SIGQUIT)
			{
				msh->prev_exit = 131;
				g_sig = 0;
			}
			if (input && *input) // solved add_history navigation issues!! :D
				add_history(input);
			nodes = parse(input, nodes, msh);
			if (nodes)
			{
				// print_nodes(nodes); // to print on terminal
				// print_nodes_file(nodes);
				exec_nodes(nodes);
				free_node_list(nodes);// after we execute the input we free the nodes )
			}
		}
			msh->prev_exit = msh->exit_code;  // ✅ Preserve correct exit code
	}
	free_msh(msh); // <------ from JESS: ho cambiato free(msh) in free_msh(msh) per libreare anche cioe' che e' all'interno della struttura (non in che casi questa funzione cerra' chiamata in questo punto, l'ho messa anche in cmd exit prima di liberare la node list)
	clear_history();
	return 0;
}
