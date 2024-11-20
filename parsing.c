/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/20 19:45:09 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create node --- if token loop happens and when node flag is true
// create redir struct
// create command struct
// create arg liked list sruct and collect args in the loop
// free functions

// create table --- before loop allocate memory for the table ()

// t_args	init_collect_args()
// {

// }

// t_cmd	init_collect_cmd()
// {

// }

// t_redirection	init_redirection_struct()
// {

// }

// t_node	init_node_struct()
// {

// }

// t_node_table	add_node_to_table()
// {

// }


// void	append_node(t_node **node_list, int n)
// {
// 	t_node	*node;
// 	t_node	*last_node;

// 	if (!node_list)
// 		return ;
// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 		return;
// 	// we
// 	node->next = NULL;
// 	if (!(*node_list))
// 	{
// 		*node_list = node;
// 		node->prev = NULL;
// 	}
// 	else
// 	{
// 		last_node = *node_list;
// 		while (last_node->next)
// 			last_node = last_node->next;
// 		last_node->next = node;
// 		node->prev = last_node;
// 	}
// }

// void	append_node(t_node *head)
// {
// 	t_node *new_node = calloc(1, sizeof(t_node));
// 	if (!new_node)
// 	{
// 		perror("calloc failed for node");
// 		free_node_list(head); // Free the existing list in case of an error
// 		return NULL;
// 	}
// 	// Set up the node links
// 	if (!head)
// 	{
// 		head = new_node; // This is the first node
// 		head->prev = NULL;
// 	}
// 	else
// 	{
// 		head->next = new_node; // Link the previous node to the new node
// 		new_node->prev = head; // Link back to the previous node
// 		new_node->prev = head; // Link back to the previous node
// 	}

// 	// Move to the new node
// 	curr_node = new_node;
// 	curr_node->node_i = node_n++; // Assign the node index

// }


//converting my logic to node creation
t_node *parse(t_mock *mock_token)
{
	int node_n = 1;					// We may need this for knowing how many nodes we have for piping? prob also for malloc?
	int token_n = 0;				// We may not need this
	bool start_node = true;			// Flag to indicate if we have to start a node at start or after pipe
	bool get_command = true;		// Flag to make the first token a command of the node (unless redir data or pipe found) - this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipe_at_start = true;  	// Flag to see if we start with a pipe, we set this to false the first token is not pipe.

	//_______ allocate node list memory______
	t_node *head = calloc(1, sizeof(t_node));
	if (!head)
		perror("calloc failed for node_table");
	// _________________________________
	// assign prev to null

	while (mock_token)
	{
		token_n++;
		// CHECKS IF WE HAVE TO START A NEW NODE
		if (start_node == true)
		{

			printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
				// _____ allocate node memory________
				// if(node n is 2 we append node)
				// t_node *new_node = calloc(1, sizeof(t_node));
				// if (!new_node)
				// {
				// 	perror("calloc failed for node");
				// 	free_node_list(head); // Free the existing list in case of an error
				// 	return NULL;
				// }
				// head->node_i = node_n - 1;
				//_________________________________
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
				// POINT: ----> here we end the node and reactivate a flag to create a new one on top of the loop
					// node->node_i = node_n; // give an index to the node
					// node->token_n = token_n; // collect number of tokens in node, if it can help
					// add node to node table
				start_node = true;  // Node created, we have to start a new node
				// node = node->next <--- here we pass to the next node because we start over again
				get_command = true; // As we start a new node we reset this flag to true
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
					get_command = false; // command found, next tokens are args
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

	free_node_list(head); // it works
	// POINT: ------> collect node in node table, node n will help in understanding how much memory to allocate?
		//if node == 0 -- either malloc failed, or node error, or input is empty, free everything?
		//if node == 1, means we have 1 node no pipes
		//if node > 1, means we have to pipe



	// Summary of AST structure
	// if (node_n == 1)
	// {
	// 	printf("\n Our TREE is made of just one node:\n a node is a command followed by arguments (strings, redirections, options, etc.)\n");
	// } else if (node_n > 1) {
	// 	printf("\n Our TREE is made of %d nodes connected by pipes within a single node table.\n", node_n);
	// }
	return NULL;
}
