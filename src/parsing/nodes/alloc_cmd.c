/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/16 18:57:13 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	alloc_cmd(t_node_list *curr_node, t_tokens *token, t_msh **msh)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf("Failed to allocate cmd in node\n");
		return (false);
	}
	cmd->cmd = ft_strdup(token->value);
	if (!cmd->cmd)
	{
		printf("Failed to allocate token->value to node cmd\n");
		return (false);
	}
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		(*msh)->found_echo = true;
	cmd->args = NULL;
	curr_node->cmd = cmd;
	return (true);
}
