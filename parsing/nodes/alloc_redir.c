/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:08:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/11 17:23:23 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void append_new_redir(t_redir **head_redir, t_redir *curr_redir)
{
	t_redir *last_redir;
	if (!(*head_redir))
	{
		*head_redir = curr_redir; // Update the the redirection data as head redir
		curr_redir->prev = NULL;
	}
	else
	{
		last_redir = *head_redir; // Traverse the redir list to find the last redir
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = curr_redir; // Append the new argument to the list
		curr_redir->prev = last_redir; // Set the previous pointer
	}
}

bool	add_target(t_tokens *token, t_redir *redir)
{
	redir->target = ft_strdup(token->next->value);
	if(!redir->target) // if dup fails.. do we even have to use dup??
	{
		printf("Minishell: Failed to add target to redir data\n");
		redir = NULL;// unsure
		return(false);
	}
	redir->target_token_type = token->next->type;
	if(redir->type == HEREDOC)
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
	return(true);
}

t_redir *init_new_redir(t_tokens **token)
{
	t_redir *redir;

	redir = calloc(1, sizeof(t_redir));
	if (!redir) // i do not free as i do it on the main
	{
		printf("Minishell: Failed to allocate redirection struct\n");
		return NULL;
	}
	redir->type = (*token)->type;
	if((*token)->next != NULL && !add_target(*token, redir)) // if token after redir exists but it fails to be allocated
		return(NULL); // return null
	*token = (*token)->next; // Advance token for the redirection target
	return (redir);
}

bool parse_redir(t_tokens **token, t_node_list	*new_node, int *redir_i)
{
	t_redir *new_redir;

	if(redir_error(*token))
		return(false);
	new_redir = init_new_redir(token); // has to go here as its where we create the redirection
	if(!new_redir)
		return (false);
	new_redir->redir_i = *redir_i;
	append_new_redir(&(new_node->redir), new_redir);
	(*redir_i)++; // Increment the redir index
	return(true);
}
