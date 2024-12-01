/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:26 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/01 17:31:20 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool alloc_cmd(t_node_list *curr_node, t_token_list *token)
{
	t_cmd *cmd;

	cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf("Failed to allocate cmd in node\n");
		return (false);
	}
	cmd->type = token->type;
	cmd->value = ft_strdup(token->value);
	if (!cmd->value)
	{
		printf("Failed to allocate token->value to node cmd\n");
		return(false);
	}
	curr_node->cmd = cmd;
	return(true);
}