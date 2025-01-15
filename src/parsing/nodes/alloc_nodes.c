/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:57:22 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/13 17:24:06 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	end_new_node(bool *start_node, t_node_list **head, t_node_list *new_node, t_tokens *token, int token_n)
{
	(void)token;
	(void)token_n;
	// printf(COLOR_RED"		%s\n"COLOR_RESET, token->value);
	// printf(COLOR_RED"		TOKEN %d: PIPE %d\n"COLOR_RESET, token_n,  token->type);
	// printf(COLOR_RED"		%s\n"COLOR_RESET, token->value);
	append_node(head, new_node);// as we end the node we have to append it to our node list
	*start_node = true;  // As we ended and appended a new node we have to flag that we are ready to start a new one
}

void append_node(t_node_list **head, t_node_list *new_node)
{
	t_node_list *last_node;

	if(!(*head))
	{
		new_node->prev = NULL;
		*head = new_node; // This updates a local copy of head
	}
	else
	{
		last_node = *head; // we do this to traverse tthrough the list without affecting it
		while(last_node->next) // we traverse the list until we reach the node that has NULL as next node
			last_node = last_node->next;
		last_node->next = new_node; // we assign the new node as last in the list
		new_node->prev = last_node; // we assign the 2nd last node as prev node of teh new node
	}
}

t_node_list *init_new_node(int node_n, bool *start_node, t_msh *msh) // nothing else needed
{
	// printf(COLOR_RED"	- NODE %i: \n"COLOR_RESET, node_n);
	t_node_list *new_node;

	new_node = calloc(1, sizeof(t_node_list));
	if (!new_node) //not freeing things here as i will do in the main if error
	{
		printf("Minishell: Failed to allocate node number %d\n", node_n);
		return NULL;
	}
	new_node->node_i = node_n - 1;
	new_node->msh = msh;
	*start_node = false; // Node has started
	return new_node;
}
