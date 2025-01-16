/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:51 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/16 12:55:36 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void free_arg_array(char **args)
{
	int i = 0;

	if (!args)
		return;
	while (args[i]) // Loop through the array until NULL
	{
		free(args[i]); // Free each argument string
		i++;
	}

	free(args); // Free the array itself
}


static void free_redir_list (t_redir *head) // need to add other frees
{
	if (!head)
		return; // unsure if needed
	t_redir *curr = head;
	// traverse and free each redirection data inside the list
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
}

void free_node_list(t_node_list *head) // frees each node in the list and its data if it was assigned
{
	if (!head)
		return; // Nothing to free if head is NULL
	t_node_list *curr = head;
	// traverse and free each node inside the list
	while (curr) // will free until curr == NULL
	{
		if(curr->cmd)
			free_cmd_struct (curr->cmd); // free elements in the cmd struct if memory was allocated to them
		free(curr->cmd); // free the cmd struct container - without it it will give leak
		if(curr->redir)
			free_redir_list (curr->redir); // free elements in the redir struct if memory was allocated to them
		// free(curr->redir);  // free the redir struct container
		t_node_list *temp = curr->next; //stores the next node of curr to then continue the loop
		free(curr);
		curr = temp;
	}
}

