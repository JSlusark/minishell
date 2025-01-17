/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:02:05 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/17 13:38:25 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_if_option(t_tokens **token)
{
	if ((*token)->value[0] != '-' || ((*token)->value[0] == '-' && (*token)->value[1] == '\0')) // Check if the token doesn't start with '-' or token is '-' only
		return(false);
	t_tokens *temp = *token; // Use a temporary pointer to avoid modifying *token
	int i = 1; // Start checking after the '-'
	while (temp->value[i] == 'n') // Check for consecutive 'n's
		i++;
	if (temp->value[i] == '\0') // Valid -n flag (only contains '-n', '-nn', etc.)
		return(true);
	else // Invalid flag (e.g., '-nm') or regular argument
		return(false);
}

void add_option_n(t_tokens **token, t_node_list *new_node)// to call add option -n
{
	if(check_if_option(token)) // if the 1st token is -n
	{
		new_node->cmd->option_n = true; // Set the -n option flag to true
		while(check_if_option(token) && (*token)->next) // while the current token is n and next token exists
		{
			if(check_if_option(&(*token)->next)) // check if next token is -n
				*token = (*token)->next;  // if so we move it as current token  (so that we do not jump non -n tokens)
			else
				break; // will always break when current token is -n so that we then move next in  the main return nodes loop
		}
	}
	else // if 1st token is not n we add it to the args
	{
		add_argument(&(new_node->cmd->args), (*token)->value); // Add to args
	}
}
