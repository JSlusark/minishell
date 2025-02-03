/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:51 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 12:20:41 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_arg_array(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_redir_list(t_redir *head)
{
	t_redir	*curr;
	t_redir	*temp;

	if (!head)
		return ;
	curr = head;
	while (curr)
	{
		// after need to add - if arg type is herdoc free this, if it's else free this other way???
		free(curr->target_name);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
}

static void	free_cmd_struct(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_arg_array(cmd->args);
	free(cmd);
}

void free_node_list(t_node_list *head)
{
	t_node_list	*curr;
	t_node_list *temp;

	if (!head)
		return ;
	curr = head;
	while (curr)
	{
		if (curr->cmd)
			free_cmd_struct (curr->cmd);
		if (curr->redir)
			free_redir_list (curr->redir);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
}
