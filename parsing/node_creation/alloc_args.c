/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:08:41 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/29 16:42:48 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void append_new_arg(t_args **cmd_args, t_args *new_arg)
{
	t_args *last_arg; // Traverse the list to find the last argument

	if (!(*cmd_args))
	{
		*cmd_args = new_arg; // Update the actual pointer to the first argument
		new_arg->prev = NULL;
	}
	else
	{
		last_arg = *cmd_args; // Traverse the list to find the last argument
		while (last_arg->next)
			last_arg = last_arg->next;
		last_arg->next = new_arg; // Append the new argument to the list
		new_arg->prev = last_arg; // Set the previous pointer
	}
}

t_args *init_new_arg(t_token_list *token)
{
	t_args *new_arg;

	new_arg = calloc(1, sizeof(t_args));
	if (!new_arg)
	{
		printf("Minishell> Failed to allocate new argument of node\n");
		// free_node_list(node_list); // Free the existing list in case of an error
		return(NULL);
	}
	new_arg->arg_type = token->type;
	new_arg->arg_value = ft_strdup(token->value); // coudl be issue when freeing the token list
	if (!new_arg->arg_value)
	{
		printf("Minishell> Failed to allocate value of new argument in node\n");
		// free(new_arg);
		// free_node_list(node_list); // Free the existing list in case of an error
		return (NULL); // if this happens it should stop so it has to return something!!!!!!!!!!!!
	}
	return(new_arg);
}