/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/21 16:04:49 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ✅ create node  - creates a node in the loop when start_node flag is true
// ✅ append node - appends the created node after we find a pipe, we also have to use this at end of loop (as ending with pipe will be error anyway and wont allocate a new node but free and return)

// create redir struct
// create command struct
// create arg liked list sruct and collect args in the loop
// free function ✅
// print fundtion ✅ (just node index for now)


// t_args	init_collect_args()
// {

// }

// t_cmd	init_collect_cmd()
// {

// }

// t_redirection	init_redirection_struct()
// {

// }

void add_cmd_to_node(t_node *node_list, t_node *curr_node, t_mock *token)
{
	t_cmd *cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return;
	}
	cmd->cmd_type = token->mock_type;
	cmd->cmd_value = ft_strdup(token->mock_value); // coudl be issue when freeing the token list
	if (!cmd->cmd_value)
	{
		perror("Failed to allocate cmd_value\n");
		free(cmd);
		free_node_list(node_list); // Free the existing list in case of an error
		return;
	}
	curr_node->cmd_data = cmd;
	// return(true);
}

void append_node(t_node **head, t_node *new_node)
{
	if(!(*head))
	{
		*head = new_node; // This updates a local copy of head
		new_node->prev = NULL;
	}
	else
	{
		t_node *last_node = *head; // we do this to traverse tthrough the list without affecting it
		while(last_node->next) // we traverse the list until we reach the node that has NULL as next node
			last_node = last_node->next;
		last_node->next = new_node; // we assign the new node as last in the list
		new_node->prev = last_node; // we assign the 2nd last node as prev node of teh new node
	}
}

t_node *create_node(t_node *node_list)
{
	t_node *new_node = calloc(1, sizeof(t_node));
	if (!new_node)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return(NULL);
	}
	return(new_node);
}


//converting my logic to node creation
t_node *parse(t_mock *mock_token)
{
	int node_n = 1;					// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int token_n = 0;				// We may not need this
	bool start_node = true;			// Flag to indicate if we have to start a node at start or after pipe
	bool get_command = true;		// Flag to make the first token a command of the node (unless redir data or pipe found) - this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipe_at_start = true;  	// Flag to see if we start with a pipe, we set this to false the first token is not pipe.

	t_node *head = NULL; 			// First node in the list
	t_node *new_node;

	printf(COLOR_GREEN"\nPARSING TOKENS...\n"COLOR_RESET);
	while (mock_token)
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
		if (mock_token->mock_type == UNKNOWN) // ERROR AND FREE
		{
			printf("Error: invalid tokens \n");
			free_node_list(head);
			return(NULL);
		}
		//CHECKS PIPES
		if (mock_token->mock_type == PIPE)
		{
			if (!mock_token->next_token || pipe_at_start || mock_token->next_token->mock_type == PIPE) // error and free
			{
				printf("Error: cannot start/end pipe and cannot have consecutive pipes\n");
				free_node_list(head);
				return(NULL);
			}
			else // we end the node here
			{
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);
				printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  mock_token->mock_type);
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);
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
			if (mock_token->mock_type == REDIR_IN || mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT || mock_token->mock_type == HEREDOC)
			{
				int redir_type = mock_token->mock_type;
				printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
				printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, token_n);
				printf("%s - %d\n", mock_token->mock_value, mock_token->mock_type);
				if(mock_token->next_token == NULL) // error and free
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					free_node_list(head);
					return(NULL); // we break the loop
				}
				// checks next token that will be file value of redir
				if(mock_token->next_token != NULL)
				{
					token_n++;
					mock_token = mock_token->next_token; // me move to the next token to check
					if (mock_token->mock_type == PIPE || mock_token->mock_type == REDIR_IN
						|| mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT
						|| mock_token->mock_type == HEREDOC) // error and free
					{
						printf(COLOR_RED"ERROR: redirection cannot be immediately followed by pipes or other redirections \n"COLOR_RESET);
						// free_node_list(head);
						return(NULL); // we break the loop as there is no point in continuing to build a node if it's an error
					}
					else
					{
						// creates the redir struct
						if(redir_type == HEREDOC) // the next token is seen as delimiter for the heredoc array
						{
							printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, token_n);
						}
						else // if redir is <, > and >> the next token is seen as file
							printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, token_n);
						printf("%s - %d\n", mock_token->mock_value, mock_token->mock_type);
					}
				}
			}
			else // CHECKS THE REST (cmd and args)
			{
				//------------> initiate command struct and args struct to see if command and args are filled of null
				printf(COLOR_BLUE"		TOKEN %d:"COLOR_RESET, token_n);
				if (get_command) // triggers command storing if true
				{
					printf("%s - %d", mock_token->mock_value, mock_token->mock_type);
					printf(COLOR_RED" (command)\n"COLOR_RESET);
					add_cmd_to_node(head, new_node, mock_token);
					get_command = false; // command found, if we have other tokens they are args if not redir data
				}
				else // triggers args storing
				{
					printf("%s - %d", mock_token->mock_value, mock_token->mock_type); // he
					printf(COLOR_RED" (arg)\n"COLOR_RESET);
				}
			}
		}
		mock_token = mock_token->next_token; // Move to the next token
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
