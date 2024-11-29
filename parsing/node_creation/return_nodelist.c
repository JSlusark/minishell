/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodelist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/29 12:48:09 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
// change calloc to FT_CALLOC
// check if forbidden functions are here

bool	unknown_token(t_token_list *token)
{
		if (token->type == UNKNOWN) // ERROR AND FREE
		{
			printf("Minishell: found invalid token %s\n", token->value);
			return(true);
		}
		return(false);
}

bool	pipe_error(t_token_list *token, bool check_pipestart)
{
	if (token->type == PIPE) // ERROR AND FREE
	{
		if (!token->next) // Check if the next token is NULL
		{
			printf("Minishell: found `%s' at end of syntax\n", token->value);
			return(true);
		}
		else if (check_pipestart || token->next->type == PIPE) // Ensure token->next is not NULL
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->value);
			return(true);
		}
	}
	return(false);
}
bool	redir_error(t_token_list *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND_OUT || token->type == HEREDOC)
	{
		if(token->next == NULL) // error and free
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			return(true); // we break the loop
		}
		else if (token->next->type == PIPE || token->next->type == REDIR_IN
			|| token->next->type == REDIR_OUT || token->next->type == APPEND_OUT
			|| token->next->type == HEREDOC || token->next->type == UNKNOWN)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->next->value);
			return(true); // we break the loop as there is no point in continuing to build a node if it's an error
		}
	}
	return(false);
}

bool add_redir(t_token_list *token, t_node	*new_node, int *redir_i)
{
	t_redir *new_redir;
	if(redir_error(token))
		return(false);
	new_redir = create_redir_data(token); // has to go here as its where we create the redirection
	if(!new_redir)
		return (false);
	new_redir->redir_i = *redir_i;
	append_redir_data(&(new_node->redir_data), new_redir);
	(*redir_i)++; // Increment the redir index
	return(true);
}

void add_cmd_and_args(bool *find_cmd, t_token_list *token, t_node *new_node, t_node *head, int token_n)
{
	if (*find_cmd) // triggers command storing if true
	{
		printf(COLOR_BLUE"		TOKEN %d - "COLOR_RESET, token_n);
		printf("%s - %d", token->value, token->type);
		printf(COLOR_RED" (command)\n"COLOR_RESET);
		add_cmd_to_node(head, new_node, token); // had to return as error
		*find_cmd = false; // command found, if we have other tokens they are args if not redir data
		// ADD ECHO -N FLAG HERE, if mocktoken->next-token_type == OPTION
	}
	else // triggers args storing
	{
		t_args *new_arg = create_newarg_data(head, token);
		append_newarg_to_cmdargs(&(new_node->cmd_args), new_arg); // Pass cmd_args as a double pointer
		printf(COLOR_BLUE"		TOKEN %d - "COLOR_RESET, token_n);
		printf("%s - %d", token->value, token->type); // he
		printf(COLOR_RED" (arg)\n"COLOR_RESET);
	}
}

void	end_new_node(bool *start_node, t_node **head, t_node *new_node, t_token_list *token, int token_n)
{
	printf(COLOR_RED"		%s\n"COLOR_RESET, token->value);
	printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  token->type);
	printf(COLOR_RED"		%s\n"COLOR_RESET, token->value);
	append_node(head, new_node);// as we end the node we have to append it to our node list
	*start_node = true;  // As we ended and appended a new node we have to flag that we are ready to start a new one
}

bool get_node_elements(bool *check_pipestart, bool *find_cmd, bool *start_node, int *redir_i, t_token_list **token, t_node **head, t_node **new_node, int *token_n)
{
	if ((*token)->type == PIPE) // As we handled pipe error handling and are grabbing our node elements, if we catch a pipe here it means that the node ends
		end_new_node(start_node, head, *new_node, *token, *token_n); // we end the new node, append to the node list and set stat_node flag to true

	else // Process redirection, command, or arguments of the new node
	{
		*check_pipestart = false; // this flag is set to false when the first token is not a pipe
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || (*token)->type == APPEND_OUT || (*token)->type == HEREDOC)
		{
			if (!add_redir(*token, *new_node, redir_i))
				return(false);
			// (*redir_i)++; // Increment the redir index
			printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
			printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, (*token_n));
			printf("%s - %d\n", (*token)->value, (*token)->type);
			*token = (*token)->next; // Advance token for the redirection target
			(*token_n)++; // used just for print
			if((*token)->type == HEREDOC) // the next token is seen as delimiter for the heredoc array
				printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, (*token_n));
			else // if redir is <, > and >> the next token is seen as file
				printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, (*token_n));
			printf("%s\n", (*token)->value);
			// token_n++;
		}
		else // Handle commands and arguments
			add_cmd_and_args(find_cmd, *token, *new_node, *head, (*token_n));
	}
	*token = (*token)->next; // Move to the next token
	// (*token_n)++; // just for print
	return(true);
}

t_node *init_new_node(int node_n, bool *start_node) // nothing else needed
{
	printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
	t_node *new_node = calloc(1, sizeof(t_node));
	if (!new_node) //not freeing things here as i will do in the main if error
	{
		printf("Minishell: Failed to allocate node number %d\n", node_n);
		return NULL;
	}
	new_node->node_i = node_n - 1;
	*start_node = false; // Node has started
	return new_node;
}

// need 3 more funcs of 20/25 lines each
t_node *return_nodelist(t_token_list *token)
{
	int	node_n;						// We this to track the amount of nodes in a list and know if and how many times we have to pipe between nodes
	int	redir_i;					// redir index
	int token_n;
	bool start_node;		// Flags minishell to start a new node, it is set to false after we init the new node and set to true when we end the new node.
	bool find_cmd;			// Flags minishell to find the command of the node: this helps with cases like "> input.txt echo hello" result and "> input.txt hello echo" error
	bool check_pipestart;  	// Flags minishell to check also if pipe is the first token when checking for pipe errors. I set this flag to false when the first token is not a pipe.
	t_node *head; 			// First node in the list
	t_node *new_node;


	redir_i = 0;
	node_n = 1;
	token_n = 1;
	start_node = true;
	find_cmd = true;
	check_pipestart = true;
	head = NULL;

	printf(COLOR_GREEN"\nPARSING TOKENS...\n"COLOR_RESET);
	while (token) //at every token iteration from the list - 1. check if token is unknown or a pipe error, 2.Start a new node, 3.Add token as element of the node and when pipe is encountered we end the node
		{
			if (unknown_token(token) || pipe_error(token, check_pipestart)) // Checks if token is unknown or a pipe error
				return NULL;
			if(start_node == true)
			{
				new_node = init_new_node(node_n, &start_node);
				if (!new_node)
					return(NULL);
				redir_i = 0; // resets redir count to 0
				find_cmd = true; //resets the find_cmd flag to true
				node_n++; // increases nodes count,
			}
			if(!get_node_elements(&check_pipestart, &find_cmd, &start_node, &redir_i, &token, &head, &new_node, &token_n)) // gets elements for the node that we created
				return(NULL);
			token_n++;
		}
		if (new_node) // Append the last node if no pipe ends it
			append_node(&head, new_node);
	return (head);
}
