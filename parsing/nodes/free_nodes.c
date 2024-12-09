/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:51 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/09 15:10:29 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static void free_arg_list (t_args *head)
{
	if (!head)
		return; // unsure if needed
	t_args *curr = head;
	// traverse and free each arg data inside the list
	while(curr)
	{
		// free(curr->arg_type);
		free(curr->value);
		t_args *temp = curr->next;
		free(curr);
		curr = temp;
	}
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
		free(curr->target);
		t_redir *temp = curr->next;
		free(curr);
		curr = temp;
	}
}

static void free_cmd_struct (t_cmd *cmd)
{
	if (!cmd)
		return; // unsure if needed
	free(cmd->value);
	// free(cmd->type);
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
		free(curr->cmd); // free the cmd struct container
		if(curr->redir)
			free_redir_list (curr->redir); // free elements in the redir struct if memory was allocated to them
		// free(curr->redir);  // free the redir struct container
		if(curr->args)
			free_arg_list (curr->args); // free elements in the struct if memory was allocated to them
		// free(curr->args);  // <--- gives issues unsure why check if without it will leak
		// free(curr->pipe); // undure if we still need this as (if node->next_node_list == NULL is what will tell us ther is another node to pipe into)
		// free(curr->node_i); // this can be useful to see the order of the node in the list
		// free(curr->node_amout); // this can be useful to see how many forks we need
		t_node_list *temp = curr->next; //stores the next node of curr to then continue the loop
		free(curr);
		curr = temp;
	}
}

