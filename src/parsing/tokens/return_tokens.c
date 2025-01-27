/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:43:06 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 13:29:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	skip_spaces(char *input, int *i)
{
	if(input[*i] == ' ') // added to solve some "" edge cases
	{
		while(input[*i] == ' ' && input[*i] != '\0') // added to solve some "" edge cases
		{
			if(input[*i + 1] != ' ') // so we land on last space and skip in the main loop, instead onf doing i-- later
				break;
			(*i)++;
		}
	}
}


t_tokens *tokenize(char *input, int *i, t_msh *msh, t_tokens *tokens) // everything should be freed here only
{
	char buff[1024];

	ft_memset(buff, 0, sizeof(buff)); // Correct usage
	(void)msh;
	skip_spaces(input, i);
	if(invalid_char(input, *i)) // check if inv chars, if false goes to next if statement
	{
		// printf(COLOR_RED"Hit invalid->"COLOR_RESET);
		// printf("input[%d]:%c\n", *i, input[*i]);
		msh->exit_code = 2;
		return (tokens);
	}
	else if(!ft_strchr(BOUNDS, input[*i])) // before itdid npt have space in bouhnds only here
	{
		// printf(COLOR_RED"Hit string->"COLOR_RESET);
		// printf("input[%d]:%c\n", *i, input[*i]);
		parse_string(input, i, msh, buff);
		append_token(&tokens, create_token(buff, ARG));
	}
	else if (!valid_bound(input, i, &tokens))
	{
		// printf(COLOR_RED"Hit bounds->"COLOR_RESET);
		// printf("input[%d]:%c\n", *i, input[*i]);
		msh->exit_code = 2;
		return (tokens);
	}
	return tokens;
}

t_tokens *return_tokens(char *input, t_msh *msh) //only free tokens here and when error update exit code
{
	int i;
	t_tokens *tokens;

	i = 0;
	tokens = NULL;
	msh->exit_code = 0; // neeed to define exit code every time to avoid prev codes being permanent
	while (input[i] != '\0')
	{
		if (msh->exit_code != 0)
			break; // just break, we check the error and free at the end (or at the main?)
		tokens = tokenize(input, &i, msh, tokens);
		// printf(COLOR_BLUE"End of tokenization ->"COLOR_RESET);
		// printf("input[%d]:%c\n\n", i, input[i]);
		if (input[i] != '\0')
			i++;
	}
	// printf("EXIT: %d\n", msh->exit_code);
	if (msh->exit_code != 0) // if the last exit code is not 0 we free and return null - this processes all errors (also the ones gave back after the loop)
	{
		free_tokens(tokens);
		return(NULL);
	}
	return(tokens); // <- return error as this
}
