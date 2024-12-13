/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/13 17:04:23 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// add check for cli input limit

bool parse_rest(bool *find_cmd, t_tokens **token, t_node_list *new_node, int token_n)
{
	t_args *new_arg;
	(void)token_n;

	if (*find_cmd) // triggers command storing if true and checks if next token is -n
	{
		// printf(COLOR_BLUE"		TOKEN_%d:"COLOR_RESET, token_n);
		// printf("%s ", (*token)->value);
		// printf(COLOR_YELLOW" <--becomes the cmd of the node\n"COLOR_RESET);
		if(!alloc_cmd(new_node, *token))// had to return as error
			return(false);
		*find_cmd = false; // command found, if we have other tokens they are args if not redir data
	}
	else // triggers args storing
	{
		if(!new_node->args &&(*token)->type == OPTION) // need to put condition of cmd args is null to avoid taking -n that follow args
			check_option(token, new_node);
		else
		{
			new_arg = init_new_arg(*token);
			if(!new_arg)
				return(false);
			append_new_arg(&(new_node->args), new_arg); // Pass args as a double pointer
			// printf(COLOR_BLUE"		TOKEN_%d:"COLOR_RESET, token_n);
			// printf(" %s", (*token)->value); // he
			// printf(COLOR_YELLOW" <--becomes an arg of the node\n"COLOR_RESET);
		}
	}
	return(true);
}

bool parse_token(t_flags *p, t_tokens **token, t_node_list **head, t_node_list **new_node)
{
	if ((*token)->type == PIPE) // As we handled pipe error handling and are grabbing our node elements, if we catch a pipe here it means that the node ends
		end_new_node(&(p->start_node), head, *new_node, *token, p->token_n); // we end the new node, append to the node list and set stat_node_list flag to true
	else // Process redirection, command, or arguments of the new node
	{
		p->pipestart = false; // this flag is set to false when the first token is not a pipe
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
		{
			// printf(COLOR_BLUE"		- REDIR STRUCT:\n"COLOR_RESET);
			// printf(COLOR_BLUE"			TOKEN_%d:"COLOR_RESET, p->token_n);
			// printf(" %s", (*token)->value);
			// printf(COLOR_YELLOW" <--becomes redirection\n"COLOR_RESET);
			if (!parse_redir(token, *new_node, &(p->redir_i))) // adds redirection and target (and advances 2 tokens from the list)
				return(false);
			p->token_n++; // used just for print
			// printf(COLOR_BLUE"			TOKEN_%d:"COLOR_RESET, p->token_n);
			// printf(" %s", (*token)->value);
			// if((*token)->type == HEREDOC) // the next token is seen as delimiter for the heredoc array
				// printf(COLOR_YELLOW" <--becomes redirection's delimiter\n"COLOR_RESET);
			// else // if redir is <, > and >> the next token is seen as file
				// printf(COLOR_YELLOW" <--becomes redirection's file\n"COLOR_RESET);
		}
		else // Parses commands and arguments
			if(!parse_rest(&(p->find_cmd), token, *new_node, p->token_n))
				return(NULL);
	}
	*token = (*token)->next; // Move to the next token (usually hits cmd, arg or redir symbol)
	return(true);
}

t_flags assign_data()
{
	t_flags param;

	param.node_n = 1;				// Initialize node count
	param.redir_i = 0;				// Initialize redirection index
	param.token_n = 1;				// Initialize token count
	param.start_node = true;		// Flag to indicate if a new node needs to start
	param.find_cmd = true;			// Flag to indicate if a command needs to be found
	param.pipestart = true;	// Flag to check if the first token is a pipe

	return param;
}


t_node_list *return_nodes(t_tokens *token)
{
	t_flags	p;				// i created this to avoud putting more than 4 args in the parse tokens
	t_node_list *head; 			// First node in the list
	t_node_list *new_node;

	p = assign_data();
	head = NULL;
	// printf(COLOR_GREEN"\nPARSING TOKENS...\n"COLOR_RESET);
	while (token) //at every token iteration from the list - 1. check if token is unknown or a pipe error, 2.Start a new node, 3.Add token as element of the node and when pipe is encountered we end the node
	{
		if (unknown_token(token) || pipe_error(token, p.pipestart)) // Checks if token is unknown or a pipe error
		{
			free_node_list(head);
			free_node_list(new_node);
			return NULL;
		}
		if(p.start_node == true)
		{
			new_node = init_new_node(p.node_n, &p.start_node);
			if (!new_node)
				return(NULL);
			p.find_cmd = true;
			p.redir_i = 0;
			p.node_n++; // increases nodes count,
		}
		if(!parse_token(&p, &token, &head, &new_node)) // gets elements for the node that we created
		{
			free_node_list(head);
			free_node_list(new_node);
			return(NULL);
		}
		p.token_n++;
	}
	if (new_node) // Append the last node if no pipe ends it
		append_node(&head, new_node);
	return (head);
}
