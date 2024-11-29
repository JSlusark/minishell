/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodelist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/29 17:39:22 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
// add check for cli input limit

// bool option_found(t_node *new_node, t_token_list *token)
// {
// 	if(token->type == OPTION)
// 	{
// 		new_node->option_n= true;
// 		*token = (*token)->next;
// 		return(true);
// 	}
// 	return(false);
// }

bool parse_rest(bool *find_cmd, t_token_list **token, t_node *new_node, int token_n)
{
	t_args *new_arg;

	if (*find_cmd) // triggers command storing if true and checks if next token is -n
	{
		printf(COLOR_BLUE"		TOKEN %d - "COLOR_RESET, token_n);
		printf("%s - %d", (*token)->value, (*token)->type);
		printf(COLOR_RED" (command)\n"COLOR_RESET);
		if(!add_cmd_to_node(new_node, *token))// had to return as error
			return(false);
		*find_cmd = false; // command found, if we have other tokens they are args if not redir data
	}
	else // triggers args storing
	{
		if(new_node->option_n == false && !new_node->cmd_args &&(*token)->type == OPTION) // need to put condition of cmd args is null to avoid taking -n that follow args
		{
			while ((*token)->type == OPTION)// while loop may cover edgecases when we have more than one consec -n
			{
				new_node->option_n = true; // Set the node's option flag
				if (!(*token)->next)
					break;
				*token = (*token)->next;  // Move to the option toke
			}
			new_arg = init_new_arg(*token);
			if(!new_arg)
				return(false);
			append_new_arg(&(new_node->cmd_args), new_arg); // Pass cmd_args as a double pointer
		}
		else
		{
			new_arg = init_new_arg(*token);
			if(!new_arg)
				return(false);
			append_new_arg(&(new_node->cmd_args), new_arg); // Pass cmd_args as a double pointer
			printf(COLOR_BLUE"		TOKEN %d - "COLOR_RESET, token_n);
			printf("%s - %d", (*token)->value, (*token)->type); // he
			printf(COLOR_RED" (arg)\n"COLOR_RESET);
		}
	}
	return(true);
}

bool parse_token(bool *check_pipestart, bool *find_cmd, bool *start_node, int *redir_i, t_token_list **token, t_node **head, t_node **new_node, int *token_n)
{
	if ((*token)->type == PIPE) // As we handled pipe error handling and are grabbing our node elements, if we catch a pipe here it means that the node ends
		end_new_node(start_node, head, *new_node, *token, *token_n); // we end the new node, append to the node list and set stat_node flag to true
	else // Process redirection, command, or arguments of the new node
	{
		*check_pipestart = false; // this flag is set to false when the first token is not a pipe
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || (*token)->type == APPEND_OUT || (*token)->type == HEREDOC)
		{
			printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
			printf(COLOR_BLUE"			TOKEN %d - Redirection:"COLOR_RESET, (*token_n));
			printf("%s - %d\n", (*token)->value, (*token)->type);
			if (!parse_redir(token, *new_node, redir_i)) // adds redirection and target (and advances 2 tokens from the list)
				return(false);
			(*token_n)++; // used just for print
			if((*token)->type == HEREDOC) // the next token is seen as delimiter for the heredoc array
				printf(COLOR_BLUE"			TOKEN %d - delimiter:"COLOR_RESET, (*token_n));
			else // if redir is <, > and >> the next token is seen as file
				printf(COLOR_BLUE"			TOKEN %d - file:"COLOR_RESET, (*token_n));
			printf("%s\n", (*token)->value);
		}
		else // Parses commands and arguments
			if(!parse_rest(find_cmd, token, *new_node, (*token_n)))
				return(NULL);
	}
	*token = (*token)->next; // Move to the next token (usually hits cmd, arg or redir symbol)
	return(true);
}

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


	head = NULL;
	redir_i = 0;
	node_n = 1;
	token_n = 1;
	start_node = true;
	find_cmd = true;
	check_pipestart = true;

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
			if(!parse_token(&check_pipestart, &find_cmd, &start_node, &redir_i, &token, &head, &new_node, &token_n)) // gets elements for the node that we created
				return(NULL);
			token_n++;
		}
		if (new_node) // Append the last node if no pipe ends it
			append_node(&head, new_node);
	return (head);
}
