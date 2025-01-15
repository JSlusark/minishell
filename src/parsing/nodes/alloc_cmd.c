/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 11:57:51 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool alloc_cmd(t_node_list *curr_node, t_tokens *token)
{
	t_cmd *cmd;

	cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf("Failed to allocate cmd in node\n");
		return (false);
	}
	// cmd->type = token->type;
	cmd->cmd = ft_strdup(token->value);
	if (!cmd->cmd)
	{
		printf("Failed to allocate token->value to node cmd\n");
		return(false);
	}
	cmd->args = NULL; // init args before allocating if any are there
	curr_node->cmd = cmd;
	return(true);
}
