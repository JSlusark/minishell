/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/20 14:26:11 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create node --- if token loop happens and when node flag is true
// create redir struct
// create command struct
// create arg liked list sruct and collect args in the loop
// free functions

// create table --- before loop allocate memory for the table ()

t_args	init_collect_args()
{

}

t_cmd	init_collect_cmd()
{

}

t_redirection	init_redirection_struct()
{

}

t_node	init_node_struct()
{

}

t_node_table	add_node_to_table()
{

}


//converting my logic to node creation
t_node_table *parse(t_mock *mock_token)
{
	int node_n = 1;					// We may need this for knowing how many nodes we have for piping? prob also for malloc?
	int token_n = 0;				// We may not need this
	bool start_node = true;			// Flag to indicate if we have to start a node at start or after pipe
	bool get_command = true;		// Flag to make the first token a command of the node (unless redir data or pipe found) - this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool pipe_at_start = true;  	// Flag to see if we start with a pipe, we set this to false the first token is not pipe.

	t_node_table *node_table = calloc(1, sizeof(t_node_table));
	if (!node_table)
		perror("calloc failed for node_table");


	while (mock_token) // We iterate through every token in our list
	{
		token_n++; // use to print the position of the token in our node - start from 0 instead than 1 perhaps?
		if (start_node == true) // flag that will make us start
		{
			printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
			t_node *node = calloc(1, sizeof(t_node));
			if (!node)
				perror("calloc failed for node");
			// POINT: ----> create node function
				//malloc create node function
				// shall i malloc every other data inside the node here?
				// node->n = 0
				// node->pipe = false; // this is set to true once we find the pipe in the non-error setting, stays to false if we do not find pipe and have 1 node
			start_node = false; // we started the node so what happens next is grabbing the node data until we find |
		}
		if (mock_token->mock_type == UNKNOWN) // interrupts node creation as it checks invalid tokens: symbols outside of string like (&&, ;, \, /, ?, unclosed ", unclosed ', ~, and * etc..) <- can we avoid tokens
		{
			printf("Error: invalid tokens \n");
			// free nodes and element inside the structs
			break;
		}
		if (mock_token->mock_type == PIPE) // checks pipe to end/start node and command or trigger error
		{
			if (!mock_token->next_token || pipe_at_start || mock_token->next_token->mock_type == PIPE) // interrupts node creation
			{
				printf("Error: cannot start/end pipe and cannot have consecutive pipes\n"); // Starting with pipe is error and we do not have to handle when a command ends with pipe
				// free nodes and elements inside structs
				break;
			}
			else // we end the node, flag to start a new one and its command
			{
				// node->pipe = true;
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);
				printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  mock_token->mock_type);
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->mock_value);

				node_n++;			// As we start a new node we increase the node number,
				// POINT: ----> here we end the node and reactivate a flag to create a new one on top of the loop
					// node->node_i = node_n; // give an index to the node
					// node->token_n = token_n; // collect number of tokens in node, if it can help
					// add node to node table
				start_node = true;  // Node created, we have to start a new node
				get_command = true; // As we start a new node we reset this flag to true
			}
		}
		else //sets pipeflag to false as if pipe is not 1st then it's not an error
		{
			pipe_at_start = false;
			//if redir grab redir and file data
			if (mock_token->mock_type == REDIR_IN || mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT || mock_token->mock_type == HEREDOC)
			{
				int redir_type = mock_token->mock_type;
				printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
				printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, token_n);
				printf("%s - %d\n", mock_token->mock_value, mock_token->mock_type);
				// Trigger error if token after redir is NULL - Redir has to be followed by something that shell will see as file
				if(mock_token->next_token == NULL)
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					// free nodes and struct data
					break; // we break the loop
				}
				// If we have a token after redir, trigger error if redir symbol is followed by redir symbol or pipe, if not we grab the file
				if(mock_token->next_token != NULL)
				{
					token_n++;
					mock_token = mock_token->next_token; // me move to the ne
					if (mock_token->mock_type == PIPE || mock_token->mock_type == REDIR_IN
						|| mock_token->mock_type == REDIR_OUT || mock_token->mock_type == APPEND_OUT
						|| mock_token->mock_type == HEREDOC) // if redir symbol is followed by |, >, >>, < and << this is considered an error
					{
						printf(COLOR_RED"ERROR: redirection cannot be immediately followed by pipes or other redirections \n"COLOR_RESET);
						// free nodes and struct
						break; // we break the loop as there is no point in continuing to build a node if it's an error
					}
					else
					{
						//----------->  create the redir struct with token and file/delimeter
						if(redir_type == HEREDOC) // the next token is seen as delimiter for the heredoc array
						{
							printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, token_n);
							//node->
						}
						else // if redir is <, > and >> the next token is seen as file
							printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, token_n);
						printf("%s - %d\n", mock_token->mock_value, mock_token->mock_type);
					}
				}
			}
			else // everything that is not redir is either node command or args
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
