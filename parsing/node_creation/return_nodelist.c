/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodelist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/25 13:19:44 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//converting my logic to node creation
t_node *return_nodelist(t_token_list *token_list)
{
	int node_n = 1;					// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int token_n = 0;				// We may not need this
	// int redir_n = 0;
	// int redir_i = 0;
	bool start_node = true;			// Flag to indicate if we have to start a node at start or after pipe
	bool get_command = true;		// Flag to make the first token a command of the node (unless redir data or pipe found) - this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipe_at_start = true;  	// Flag to see if we start with a pipe, we set this to false the first token is not pipe.

	t_node *head = NULL; 			// First node in the list
	t_node *new_node;
	// t_args *new_arg = NULL;
	// t_args *cmd_args;

	printf(COLOR_GREEN"\nPARSING TOKENS...\n"COLOR_RESET);
	while (token_list)
	{
		token_n++;
		// IF STARTNODE FLAG IS TRUE WE CREATE A NEW NODE
		if (start_node == true)
		{
			printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
			new_node = create_node(head);
			if(!new_node) // is null
				return (NULL); // no free as i did alread in the create node func
			new_node->node_i = node_n - 1;
			start_node = false;
		}
		if (token_list->type == UNKNOWN) // ERROR AND FREE
		{
			printf("Error: invalid tokens \n");
			free_node_list(head);
			return(NULL);
		}
		//CHECKS PIPES
		if (token_list->type == PIPE)
		{
			if (!token_list->next || pipe_at_start || token_list->next->type == PIPE) // error and free
			{
				printf("Error: cannot start/end pipe and cannot have consecutive pipes\n");
				free_node_list(head);
				return(NULL);
			}
			else // we end the node here
			{
				printf(COLOR_RED"		%s\n"COLOR_RESET, token_list->value);
				printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  token_list->type);
				printf(COLOR_RED"		%s\n"COLOR_RESET, token_list->value);
				node_n++;
				start_node = true;  // Node created, we have to start a new node
				get_command = true; // As we start a new node we reset this flag to true
				append_node(&head, new_node);// as we end the node we append it to our list
			}
		}
		else //sets pipeflag to false as pipe is not first command
		{
			pipe_at_start = false;
			// CHECK REDIRECTIONS & FILES
			if (token_list->type == REDIR_IN || token_list->type == REDIR_OUT || token_list->type == APPEND_OUT || token_list->type == HEREDOC)
			{
				int redir_type = token_list->type;
				printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
				printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, token_n);
				printf("%s - %d\n", token_list->value, token_list->type);
				if(token_list->next == NULL) // error and free
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					free_node_list(head);
					return(NULL); // we break the loop
				}
				// checks next token that will be file value of redir
				if(token_list->next != NULL)
				{
					// append_redir_data(new_node->redir_data);
					t_redir *new_redir = create_redir_data(head, token_list); // has to go here as its where we create the redirection
					if(!new_redir)
						return (NULL);
					append_redir_data(&(new_node->redir_data), new_redir);
					token_n++;
					token_list = token_list->next; // me move to the next token to check
					if (token_list->type == PIPE || token_list->type == REDIR_IN
						|| token_list->type == REDIR_OUT || token_list->type == APPEND_OUT
						|| token_list->type == HEREDOC) // error and free
					{
						printf(COLOR_RED"ERROR: redirection cannot be immediately followed by pipes or other redirections \n"COLOR_RESET);
						// free_node_list(head);
						return(NULL); // we break the loop as there is no point in continuing to build a node if it's an error
					}
					else
					{
						// creates the redir struct and adds redir index
						if(redir_type == HEREDOC) // the next token is seen as delimiter for the heredoc array
						{
							//adds redir data for heredoc
							printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, token_n);
						}
						else // if redir is <, > and >> the next token is seen as file
						{
							//adds redir data for the other redir types
							printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, token_n);
						}
						printf("%s - %d\n", token_list->value, token_list->type);
						// redir_i++; // increase redir index in case we have a 2nd redirection
					}
				}
			}
			else // CHECKS THE REST (cmd and args)
			{
				//------------> initiate command struct and args struct to see if command and args are filled of null
				printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
				if (get_command) // triggers command storing if true
				{
					printf("%s - %d", token_list->value, token_list->type);
					printf(COLOR_RED" (command)\n"COLOR_RESET);
					add_cmd_to_node(head, new_node, token_list); // had to return as error
					get_command = false; // command found, if we have other tokens they are args if not redir data
					// ADD ECHO -N FLAG HERE, if mocktoken->next-token_type == OPTION
					//mocktoken = mocktoken->next
					// n_echoflag = true
					//mocktoken = mocktoken->next
					// pass to next tokens
				}
				else // triggers args storing
				{
					t_args *new_arg = create_newarg_data(head, token_list);
					append_newarg_to_cmdargs(&(new_node->cmd_args), new_arg); // Pass cmd_args as a double pointer
					printf("%s - %d", token_list->value, token_list->type); // he
					printf(COLOR_RED" (arg)\n"COLOR_RESET);
				}
			}
		}
		token_list = token_list->next; // Move to the next token
	}
	append_node(&head, new_node);// we also have to append the node when it doesn't have pipe
	// POINT: ------> collect node in node table, node n will help in understanding how much memory to allocate?
		//if node == 0 -- either malloc failed, or node error, or input is empty, free everything?
		//if node == 1, means we have 1 node no pipes
		//if node > 1, means we have to pipe


	printf("	Total number of nodes detected: %d\n", node_n);



	// Summary of AST structure
	// if (node_n == 1)
	// {
	// 	printf("\n Our TREE is made of just one node:\n a node is a command followed by arguments (strings, redirections, options, etc.)\n");
	// } else if (node_n > 1) {
	// 	printf("\n Our TREE is made of %d nodes connected by pipes within a single node table.\n", node_n);
	// }
	return (head);
}
