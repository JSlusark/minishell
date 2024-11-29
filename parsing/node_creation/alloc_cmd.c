/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:26 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/29 16:11:49 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool add_cmd_to_node(t_node *curr_node, t_token_list *token)
{
	t_cmd *cmd;
	cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf("Failed to allocate cmd in node\n");
		return (false);
	}
	cmd->cmd_type = token->type;
	cmd->cmd_value = ft_strdup(token->value); // coudl be issue when freeing the token list
	if (!cmd->cmd_value)
	{
		printf("Failed to allocate token->value to node cmd\n");
		// free(cmd);
		// free_node_list(node_list); // Free the existing list in case of an error
		return(false); // if this happens it should stop so it has to return something!!!!!!!!!!!!
	}
	curr_node->cmd_data = cmd;
	return(true);
}