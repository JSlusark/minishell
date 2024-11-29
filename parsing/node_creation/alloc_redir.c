/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:08:44 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/29 12:41:40 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void append_redir_data(t_redir **head_redir, t_redir *curr_redir)
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

bool	add_redir_target(t_token_list *token, t_redir *redir)
{
	redir->target = ft_strdup(token->next->value);
	if(!redir->target) // if dup fails.. do we even have to use dup??
	{
		printf("Minishell: Failed to add target to redir data\n");
		redir = NULL;// unsure
		return(false);
	}
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
	return(true);
}

t_redir *create_redir_data(t_token_list *token)
{
	t_redir *redir = calloc(1, sizeof(t_redir));
	if (!redir) // i do not free as i do it on the main
	{
		printf("Minishell: Failed to allocate redirection struct\n");
		return NULL;
	}
	redir->redir_type = token->type;
	if(token->next != NULL && !add_redir_target(token, redir)) // if token after redir exists but it fails to be allocated
		return(NULL); // return null
	return (redir);
}
