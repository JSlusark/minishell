/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:36:50 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/12 15:38:32 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// These functions return true if error or false if not error

bool	unknown_token(t_tokens *token)
{
		if (token->type == UNKNOWN) // ERROR AND FREE
		{
			printf("Minishell: found invalid token %s\n", token->value);
			return(true);
		}
		return(false);
}

bool	pipe_error(t_tokens *token, bool check_pipestart)
{
	if (token->type == PIPE) // ERROR AND FREE
	{
		if (!token->next) // Check if the next token is NULL
		{
			printf("Minishell: found `%s' at end of syntax\n", token->value);
			return(true);
		}
		else if (check_pipestart || token->next->type == PIPE) // Ensure token->next is not NULL
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->value);
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
