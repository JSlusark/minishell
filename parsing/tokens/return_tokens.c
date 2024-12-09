/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/09 16:14:40 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quote_closed(int i, char *input)
{
	int j = i++;
	while(input[j] && input[j] != '"')
		j++;
	if(input[j] == '"')
		printf("closure found\n");
	else
		printf("closure not found\n");
}

void free_mock_tokens(t_token_list *head)
{
	t_token_list *current = head;
	t_token_list *next;

	while (current != NULL)
	{
		next = current->next; // Store the next token
		free(current->value); // Free the duplicated string
		free(current);             // Free the current node
		current = next;            // Move to the next token
	}
}
t_token_list *return_tokens(char *input)
{
	// t_token_list *head = NULL;      // Head of the linked list
	// t_token_list *current = NULL;   // Current node in the linked list
	int i;
	// char *bounds; // used when we have stuff like echo|echo

	// bounds = "|>" // not sure what to do with ec"h"o or echo"hello" , spaces could help me?
	i = 0;
	while(input[i])
	{
		// t_token_list *new_token = malloc(sizeof(t_token_list));
		write(1, &input[i], 1);
		write(1, "\n", 1);
		if(input[i] == '"')
		{
			quote_closed(i, input);
			// if(quote_closed(input[i]))
			// {

			// 	// new_token->value = collect_str();
			// 	// new_token->type = D_STRING;
			// }
			// else
			// {
			// 	printf("Minishell: Error with d_str");
			// 	return (NULL);
			// }
		}
		// else if(input[i] == "'")
		// {
		// 	if(is_s_str(input[i]))
		// 	{
		// 		new_token->value = collect_str();
		// 		new_token->type = S_STRING;
		// 		printf("Minishell: Error with s_str");
		// 	}
		// }
		i++;
	}
	return(NULL); // <- return error as this
}




/*






*/
