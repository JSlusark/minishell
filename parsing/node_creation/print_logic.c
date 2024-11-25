/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/25 12:54:32 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


/*
	Will need to clean this up after i cleanup print_nodes
*/


void append_redir_data(t_redir **head_redir, t_redir *curr_redir)
{
	if (!(*head_redir))
	{
		*head_redir = curr_redir; // Update the the redirection data as head redir
		curr_redir->prev = NULL;
	} else {
		t_redir *last_redir = *head_redir; // Traverse the redir list to find the last redir
		while (last_redir->next) {
			last_redir = last_redir->next;
		}
		last_redir->next = curr_redir; // Append the new argument to the list
		curr_redir->prev = last_redir; // Set the previous pointer
	}
}

t_redir *create_redir_data(t_node *node_list, t_token_list *token)
{
	t_redir *redir = calloc(1, sizeof(t_redir));
	if (!redir)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return NULL;
	}
	redir->redir_type = token->type;
	if(token->next != NULL)
	{
		redir->target = ft_strdup(token->next->value);
		redir->target_token_type = token->next->type;
		if(redir->redir_type == HEREDOC)
			redir->target_type = TARGET_DELIMITER;
		else
		{
			if(token->next->type == ABS_PATH || token->next->type == REL_PATH)
				redir->target_type = TARGET_PATHNAME; // after parsing we need to see if the target is an ENV_VAR
			else if(token->next->type == ENV_VAR)
				redir->target_type = TARGET_ENV_PATHNAME; // after parsing we need to see if the target is an ENV_VAR
			else
				redir->target_type = TARGET_FILENAME;
		}
	}
	return (redir);
	// curr_node->redir_data = redir;
}

void append_newarg_to_cmdargs(t_args **cmd_args, t_args *new_arg)
{
	if (!(*cmd_args)) {
		*cmd_args = new_arg; // Update the actual pointer to the first argument
		new_arg->prev = NULL;
	} else {
		t_args *last_arg = *cmd_args; // Traverse the list to find the last argument
		while (last_arg->next) {
			last_arg = last_arg->next;
		}
		last_arg->next = new_arg; // Append the new argument to the list
		new_arg->prev = last_arg; // Set the previous pointer
	}
}

t_args *create_newarg_data(t_node *node_list, t_token_list *token)
{
	t_args *new_arg = calloc(1, sizeof(t_args));
	if (!new_arg)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return(NULL);
	}
	new_arg->arg_type = token->type;
	new_arg->arg_value = ft_strdup(token->value); // coudl be issue when freeing the token list
	if (!new_arg->arg_value)
	{
		perror("Failed to allocate arg_value\n");
		free(new_arg);
		free_node_list(node_list); // Free the existing list in case of an error
		return (NULL); // if this happens it should stop so it has to return something!!!!!!!!!!!!
	}
	return(new_arg);
}

void add_cmdargs_to_node(t_node *node_list, t_node *curr_node, t_args *head_arg)
{
	// t_args *head_arg = calloc(1, sizeof(t_args));
	if (!head_arg)
	{
		perror("Failed to allocate cmd_args\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return;
	}



	// cmd->cmd_type = token->type;
	// cmd->cmd_value = ft_strdup(token->value); // coudl be issue when freeing the token list
	// if (!cmd->cmd_value)
	// {
	// 	perror("Failed to allocate cmd_value\n");
	// 	free(cmd);
	// 	free_node_list(node_list); // Free the existing list in case of an error
	// 	return; // if this happens it should stop so it has to return something!!!!!!!!!!!!
	// }
	curr_node->cmd_args = head_arg;
	// return(true);
}



void add_cmd_to_node(t_node *node_list, t_node *curr_node, t_token_list *token)
{
	t_cmd *cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		perror("Failed to allocate node\n");
		free_node_list(node_list); // Free the existing list in case of an error
		return;
	}
	cmd->cmd_type = token->type;
	cmd->cmd_value = ft_strdup(token->value); // coudl be issue when freeing the token list
	if (!cmd->cmd_value)
	{
		perror("Failed to allocate cmd_value\n");
		free(cmd);
		free_node_list(node_list); // Free the existing list in case of an error
		return; // if this happens it should stop so it has to return something!!!!!!!!!!!!
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
		// last_node->next->next = NULL;
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
t_node *parse(t_token_list *mock_token)
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
		if (mock_token->type == UNKNOWN) // ERROR AND FREE
		{
			printf("Error: invalid tokens \n");
			free_node_list(head);
			return(NULL);
		}
		//CHECKS PIPES
		if (mock_token->type == PIPE)
		{
			if (!mock_token->next || pipe_at_start || mock_token->next->type == PIPE) // error and free
			{
				printf("Error: cannot start/end pipe and cannot have consecutive pipes\n");
				free_node_list(head);
				return(NULL);
			}
			else // we end the node here
			{
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->value);
				printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  mock_token->type);
				printf(COLOR_RED"		%s\n"COLOR_RESET, mock_token->value);
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
			if (mock_token->type == REDIR_IN || mock_token->type == REDIR_OUT || mock_token->type == APPEND_OUT || mock_token->type == HEREDOC)
			{
				int redir_type = mock_token->type;
				printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
				printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, token_n);
				printf("%s - %d\n", mock_token->value, mock_token->type);
				if(mock_token->next == NULL) // error and free
				{
					printf(COLOR_RED"ERROR: redirections need to be followed by a file! \n"COLOR_RESET);
					free_node_list(head);
					return(NULL); // we break the loop
				}
				// checks next token that will be file value of redir
				if(mock_token->next != NULL)
				{
					// append_redir_data(new_node->redir_data);
					t_redir *new_redir = create_redir_data(head, mock_token); // has to go here as its where we create the redirection
					if(!new_redir)
						return (NULL);
					append_redir_data(&(new_node->redir_data), new_redir);
					token_n++;
					mock_token = mock_token->next; // me move to the next token to check
					if (mock_token->type == PIPE || mock_token->type == REDIR_IN
						|| mock_token->type == REDIR_OUT || mock_token->type == APPEND_OUT
						|| mock_token->type == HEREDOC) // error and free
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
						printf("%s - %d\n", mock_token->value, mock_token->type);
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
					printf("%s - %d", mock_token->value, mock_token->type);
					printf(COLOR_RED" (command)\n"COLOR_RESET);
					add_cmd_to_node(head, new_node, mock_token); // had to return as error
					get_command = false; // command found, if we have other tokens they are args if not redir data
					// ADD ECHO -N FLAG HERE, if mocktoken->next-token_type == OPTION
					//mocktoken = mocktoken->next
					// n_echoflag = true
					//mocktoken = mocktoken->next
					// pass to next tokens
				}
				else // triggers args storing
				{
					t_args *new_arg = create_newarg_data(head, mock_token);
					append_newarg_to_cmdargs(&(new_node->cmd_args), new_arg); // Pass cmd_args as a double pointer
					printf("%s - %d", mock_token->value, mock_token->type); // he
					printf(COLOR_RED" (arg)\n"COLOR_RESET);
				}
			}
		}
		mock_token = mock_token->next; // Move to the next token
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
