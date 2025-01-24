/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:35:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 11:35:53 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void free_tokens(t_tokens *head)
{
	t_tokens *current;
	while (head)
	{
		current = head;
		head = head->next;
		free(current->value);
		free(current);
	}
}
t_tokens *create_token(const char *value, int type)
{
		t_tokens *new_token = malloc(sizeof(t_tokens));
		if (!new_token)
			return NULL;
		new_token->value = strdup(value);
		if (!new_token->value)
		{
			free(new_token);
			return NULL;
		}
		new_token->type = type;
		new_token->next = NULL;
		// printf("TOKEN:%s", new_token->value);
		return new_token;
}

void append_token(t_tokens **head, t_tokens *new_token)
{
	if (!*head)
	{
		*head = new_token;
		return;
	}
	t_tokens *current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}