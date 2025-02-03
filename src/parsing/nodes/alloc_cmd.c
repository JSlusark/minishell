/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 11:54:48 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	alloc_cmd(t_node_list *curr_node, t_tokens *token, t_flags **p)
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
		(*p)->found_echo = true;
	cmd->args = NULL;
	curr_node->cmd = cmd;
	return (true);
}
