/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:02:05 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 20:07:35 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_if_option(t_tokens **token, t_node_list *new_node)
{
	if ((*token)->value[0] != '-' || ((*token)->value[0] == '-' && (*token)->value[1] == '\0')) // Check if the token doesn't start with '-' or token is '-' only
	{
		add_argument(&(new_node->cmd->args), (*token)->value); // Add to args
		return(false);
	}
	t_tokens *temp = *token; // Use a temporary pointer to avoid modifying *token
	int i = 1; // Start checking after the '-'
	while (temp->value[i] == 'n') // Check for consecutive 'n's
		i++;
	if (temp->value[i] == '\0') // Valid -n flag (only contains '-n', '-nn', etc.)
	{
		new_node->cmd->option_n = true; // Set the -n option flag
		return(true);
	}
	else // Invalid flag (e.g., '-nm') or regular argument
	{
		add_argument(&(new_node->cmd->args), (*token)->value); // Add to args
		return(false);
	}
}

void add_option_n(t_tokens **token, t_node_list *new_node)// to call add option -n
{
	while(check_if_option(token, new_node)) // if the 1st token is -n loop and move forward until we find a token that is not
	{
		if((*token)->next)
			*token = (*token)->next;  // Move to the option toke
		else
			break;
	}
}
