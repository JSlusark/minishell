/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:36:50 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/16 17:51:41 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


// I REMOVED THIS AS  ALREADY CHECK THIS ERROR IN THE TOKENIZER
// bool	unknown_token(t_tokens *token, t_node_list *head, t_node_list * new_node)
// {
// 		if (token->type == UNKNOWN) // ERROR AND FREE
// 		{
// 			printf("Minishell: found invalid token %s\n", token->value);
// 			free_node_list(new_node); //
// 			free_node_list(head);
// 			return(true);
// 		}
// 		return(false);
// }

bool	pipe_error(t_tokens *token, bool check_pipestart, t_node_list *head, t_node_list * new_node)
{
	if (token->type == PIPE) // ERROR AND FREE
	{
		if (check_pipestart)
		{
			printf("Minishell: found `%s' at begining of syntax\n", token->value);
			// i do not need to free here as in the case we don't inizialised any nodes or continue parsing the tokens after |
			return(true);
		}
		else if (!token->next) // Check if the next token is NULL
		{
			printf("Minishell: found `%s' at end of syntax\n", token->value);
			free_node_list(new_node); // we have to free the new node which was not appended to the list because of the error
			free_node_list(head); // we also need to free the list in case there were other nodes created and appended before the issue
			return(true);
		}
		else if (token->next->type == PIPE) // Ensure token->next is not NULL
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->value);
			free_node_list(new_node); // we have to free the new node which was not appended to the list because of the error
			free_node_list(head); // we also need to free the list in case there were other nodes created and appended before the issue
			return(true);
		}
	}
	return(false);
}
bool	redir_error(t_tokens *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND || token->type == HEREDOC)
	{
		if(token->next == NULL) // error and free
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			return(true); // we break the loop
		}
		else if (token->next->type == PIPE || token->next->type == REDIR_IN
			|| token->next->type == REDIR_OUT || token->next->type == APPEND
			|| token->next->type == HEREDOC || token->next->type == UNKNOWN)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->next->value);
			return(true); // we break the loop as there is no point in continuing to build a node if it's an error
		}
	}
	return(false);
}
