/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:08:41 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/01 17:32:11 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void append_new_arg(t_args **args, t_args *new_arg)
{
	t_args *last_arg;

	if (!(*args))
	{
		*args = new_arg;
		new_arg->prev = NULL;
	}
	else
	{
		last_arg = *args;
		while (last_arg->next)
			last_arg = last_arg->next;
		last_arg->next = new_arg;
		new_arg->prev = last_arg;
	}
}

t_args *init_new_arg(t_token_list *token)
{
	t_args *new_arg;

	new_arg = calloc(1, sizeof(t_args));
	if (!new_arg)
	{
		printf("Minishell> Failed to allocate new argument of node\n");
		return(NULL);
	}
	new_arg->type = token->type;
	new_arg->value = ft_strdup(token->value);
	if (!new_arg->value)
	{
		printf("Minishell> Failed to allocate value of new argument in node\n");
		return (NULL);
	}
	return(new_arg);
}