/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:51 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/16 15:51:36 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void free_arg_array(char **args)
{
	int i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}


static void free_redir_list (t_redir *head)
{
	if (!head)
		return; // unsure if needed
	t_redir *curr = head;
	while(curr)
	{
		// after need to add - if arg type is herdoc free this, if it's else free this other way
		// free(curr->type);
		free(curr->target_name);
		t_redir *temp = curr->next;
		free(curr);
		curr = temp;
	}
}

static void free_cmd_struct (t_cmd *cmd)
{
	if (!cmd)
		return; // unsure if needed
	free(cmd->cmd);
	if(cmd->args)
		free_arg_array(cmd->args);
	free(cmd);
}

void free_node_list(t_node_list *head)
{
	if (!head)
		return;
	t_node_list *curr = head;
	while (curr)
	{
		if(curr->cmd)
			free_cmd_struct (curr->cmd);
		if(curr->redir)
			free_redir_list (curr->redir);
		t_node_list *temp = curr->next;
		free(curr);
		curr = temp;
	}
}

