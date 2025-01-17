/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/17 17:15:32 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool parse_rest(t_tokens **token, t_node_list *new_node, int token_n, t_flags **p)
{
	if ((*p)->find_cmd) // triggers command storing if true and checks if next token is -n
	{
		(void)token_n;
		if(!alloc_cmd(new_node, *token, p))// had to return as error
			return(false);
		(*p)->find_cmd = false; // command found, if we have other tokens they are args if not redir data
	}
	else // triggers args storing // this should not execute i
	{
		if((*p)->found_echo && !new_node->cmd->args && new_node->cmd->option_n == false) // adds -n flag if cmd of node is echo, there are no args yet and flag is false
			add_option_n(token, new_node); // <--- adds -n flag and skips other -n until token->next is not -n, it lands to the last -n before non -n token
		else
		{
			 if (!add_argument(&(new_node->cmd->args), (*token)->value))
				return false;
		}
	}
	return (true);
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
			if (!parse_redir(token, *new_node, &(p->redir_i))) // adds redirection and target (and advances the only the redire tokens from the list, we advance the redir in line 60 as it applies to the main token iteration )
				return(false);
			p->token_n++; // used just for printer
		}
		else // Parses commands and arguments
			if(!parse_rest(token, *new_node, p->token_n, &p))
				return(false);
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
	param.found_echo = false; // <--- added this flag so that we use alloc option only with echo, it turns true when cmd token is echo

	return (param);
}

t_node_list *return_nodes(t_tokens *token, t_msh *msh)
{
	t_flags	p;				// i created this to avoud putting more than 4 args in the parse tokens
	t_node_list *head;		// First node in the list
	t_node_list *new_node;

	p = assign_data();
	head = NULL;
	while (token != NULL) //at every token iteration from the list - 1. check if token is unknown or a pipe error, 2.Start a new node, 3.Add token as element of the node and when pipe is encountered we end the node
	{
		if (pipe_error(token, p.pipestart, head, new_node)) // removed unknow token as that error is covere already in the tokenizer
			return (NULL);
		if(p.start_node == true)
		{
			new_node = init_new_node(p.node_n, &p.start_node, msh);
			if (!new_node)
				return(NULL);
			p.find_cmd = true;
			p.found_echo = false; // <--- added this flag so that we use alloc option only with echo, it turns true when cmd token is echo
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
