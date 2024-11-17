/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/17 19:07:22 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
The current parsing function doesn't actually build nodes yet.
Instead, it is designed to analyze and show how Bash interprets the input we pass to it and create our nodes.
I think this is essential for us so that we can both agree on how things will work before we build our data structures and execution functions.
I left some notes for you in a folder called how_bash_parses_tokens:
	- bash_parse_explained.c
	- parsing_rules.c

I decided to do this so that we can already see a structure and understand how to progress within our project, improve our code and avoid special
cases that will make things harder for us to fix. It's been a bit hard at the beginning but I feel that i needed to do this
to avoid impulsive decisions in building our parsing structure and finding myself with a mess that would make things more confusing for all of us.

I just need to add some other small details to this code today.
Once i am done I will use this same logic to build our nodes and another file called print_nodes.c
which will print the nodes that I created.

 */

t_node_table *parse(t_mock *mock_token)
{
	int node_n = 1;
	int token_n = 0;
	int is_node_command = true;
	int print_node_number = 1;   // Flag to print node number only once per node
	bool pipe_at_start = true;   // Flag to see if we start with a pipe and therefore error ->

	while (mock_token)
	{
		token_n++;

		if (print_node_number == 1)
		{
			printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
			print_node_number = 0; // Reset flag after printing the node number
		}
		if (mock_token->mock_type == PIPE)
		{
			if (!mock_token->next_token || pipe_at_start) // i have to change this, because we can end input with a pipe in bash
				printf("ERROR: Cannot start or end node with a pipe!\n"); // Check for invalid pipe position
			else
			{
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);
				printf(COLOR_RED"		TOKEN %d: PIPE\n"COLOR_RESET, token_n);
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);
				node_n++;
				is_node_command = true;
				print_node_number = 1;      // Reset to print new node number
			}
		}
		else
		{
			pipe_at_start = false;
			if (mock_token->mock_type == REDIR_IN || mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT || mock_token->mock_type == HEREDOC)
			{
				int redir_type = mock_token->mock_type;
				printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
				printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, token_n);
				printf("%s\n", mock_token->mock_value);
				if(mock_token->next_token == NULL) // important: every redir type has to be always followed by a token and the token that follows it will always be considered a file (for <, >, >>) or delimiter (for HEREDOC <<)
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					break; // we break the loop
				}
				if(mock_token->next_token != NULL) // the token that immediately comes after a redirection will always be considered a file (for <, >, >>) or delimiter (for HEREDOC)
				{
					token_n++;
					mock_token = mock_token->next_token;
					if (mock_token->mock_type == PIPE || mock_token->mock_type == REDIR_IN
						|| mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT
						|| mock_token->mock_type == HEREDOC) // if redir symbol is followed by |, >, >>, < and << this is considered an error
					{
						printf(COLOR_RED"ERROR: redirection cannot be immediately followed by pipes or other redirections \n"COLOR_RESET);
						break; // we break the loop as there is no point in continuing to build a node if it's an error
					}
					else
					{
						if(redir_type == HEREDOC) // the next token is seen as delimiter for the heredoc array
							printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, token_n); // this is either
						else // if redir is <, > and >> the next token is seen as file
							printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, token_n);
						printf("%s\n", mock_token->mock_value);
					}
				}
			}
			else
			{
				printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
				if (is_node_command)
				{
					printf("%s", mock_token->mock_value);
					printf(COLOR_RED" (command)\n"COLOR_RESET);
					is_node_command = false;
				}
				else
				{
					printf("%s", mock_token->mock_value);
					printf(COLOR_RED" (arg)\n"COLOR_RESET);
				}
			}
		}
		mock_token = mock_token->next_token; // Move to the next token
	}
	// Summary of AST structure
	if (node_n == 1)
	{
		printf("\n Our TREE is made of just one node:\n a node is a command followed by arguments (strings, redirections, options, etc.)\n");
	} else if (node_n > 1) {
		printf("\n Our TREE is made of %d nodes connected by pipes within a single node table.\n", node_n);
	}
	return NULL;
}
