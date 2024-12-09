/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:02:05 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/01 17:04:10 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_option(t_token_list **token, t_node_list *new_node)
{
	while ((*token)->type == OPTION)// while loop may cover edgecases when we have more than one consec -n
	{
		new_node->option_n = true; // Set the node's option flag
		if ((*token)->next && (*token)->next->type == OPTION)
			*token = (*token)->next;  // Move to the option toke
		else
			break;
	}
}