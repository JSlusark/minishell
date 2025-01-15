/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:08:41 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 11:56:46 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


bool add_argument(char ***args, char *new_arg)
{
	int count = 0;

	if (*args)
	{
		while ((*args)[count]) // Count existing arguments
			count++;
	}

	char **new_array = realloc(*args, sizeof(char *) * (count + 2)); // +1 for new arg, +1 for NULL terminator
	if (!new_array)
		return false;

	new_array[count] = strdup(new_arg);  // Add new argument
	if (!new_array[count])
		return false;

	new_array[count + 1] = NULL;  // Ensure NULL-terminated
	*args = new_array;

	return true;
}


// void append_new_arg(t_args **args, t_args *new_arg)
// {
// 	t_args *last_arg;

// 	if (!(*args))
// 	{
// 		*args = new_arg;
// 		new_arg->prev = NULL;
// 	}
// 	else
// 	{
// 		last_arg = *args;
// 		while (last_arg->next)
// 			last_arg = last_arg->next;
// 		last_arg->next = new_arg;
// 		new_arg->prev = last_arg;
// 	}
// }

// t_args *init_new_arg(t_tokens *token)
// {
// 	t_args *new_arg;

// 	new_arg = calloc(1, sizeof(t_args));
// 	if (!new_arg)
// 	{
// 		printf("Minishell> Failed to allocate new argument of node\n");
// 		return(NULL);
// 	}
// 	new_arg->type = token->type;
// 	new_arg->value = ft_strdup(token->value);
// 	if (!new_arg->value)
// 	{
// 		printf("Minishell> Failed to allocate value of new argument in node\n");
// 		return (NULL);
// 	}
// 	return(new_arg);
// }
