/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 19:42:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_empty_string(int *i, char *input)
{
	printf("last_quote_pos: %d c: %c\n", *i, input[*i]); // ""
	int prev_i = *i - 2; // character before the 2nd and 1st quote
	int next_i = *i + 1; // character after the 2nd quote
	printf("prev_i: %d next_i: %d\n", prev_i, next_i);

	if((prev_i  < 0 || input[prev_i] == ' ') && (input[next_i] == ' ' || input[next_i] == '\0' ))
		return(true); // stops and appends a token with space (cases where "" is empty and delimited by spaces or start/end string delimiters)

	return(false);
}



t_tokens *parse_string(char *input, int *i, t_msh *msh, t_tokens *tokens)
{
	char buff[1024];
	int buff_len;

	buff_len = 0;
	memset(buff, 0, sizeof(buff));

	while (!ft_strchr(BOUNDS, input[*i]) && input[*i] != '\0')
	{
		if (ft_strchr(QUOTES, input[*i]))
		{
			printf(COLOR_CYAN"START OF QUOTE STRING - "COLOR_RESET);
			printf("input[%d]: %c\n", *i, input[*i]);
			bool closure = false;
			char quote = input[*i];
			// printf("Found quote: %c at input[%d]\n", quote, *i);
			(*i)++; // Skip the opening quote
			if(input[*i] == '\0') // if first quote followed by \0 error
			{
				msh->exit_code = 2;
				printf("Minishell: %c at input[%d] had no closure\n", quote, *i);
				return(tokens);
			}
			// int buff_len = 0;
			while (input[*i] != '\0') // collect buffer until end
			{
				if (input[*i] == quote) // or until closed quote
				{
					printf("Closing quote: %c at input[%d]\n", quote, *i);
					closure = true;
					break;
				}
				buff[buff_len++] = input[*i]; // add characters to buff
				if (buff_len >= 1024) // if buff overflow
				{
					printf("Minishell: buffer overflow\n");
					msh->exit_code = 1;
					return (tokens);
				}
				(*i)++;
			}
			// i stops at \0 or quote
			if(input[*i] == '\0' && !closure) // if not closed  and stops at null error
			{
				msh->exit_code = 2;
				printf("Minishell: %c at input[%d] had no closure\n", quote, *i);
				return(tokens);
			}
			if(input[*i + 1] == ' ' || input[*i + 1] == '\0' || ft_strchr(BOUNDS, input[*i + 1])) // we append only if we find space or BOUNDS
			{
				buff[buff_len] = '\0'; // Null-terminate only when we know e have to
				if (buff_len > 0)
					append_token(&tokens, create_token(buff, ARG));
				else if(check_empty_string(i, input)) // if empty string is delimited by spaces or delimiters returns
				{
					*buff = ' ';
					// char empty = ' ';
					append_token(&tokens, create_token(buff, ARG));
				}
				buff_len = 0; // reset the len of the buff
				return(tokens); // last i is on last QUOTE
			}
			(*i)++; // skip the ending quote only if we have to continue because no space or BOUNDS found
		}
		else
		{
			// int buff_len = 0;
			while (input[*i] != '\0') // collect buffer and stop at BOUNDS
			{
				printf("input[%d]: %c\n", *i , input[*i]);
				// if (input[*i] == ' ')
				if (ft_strchr(BOUNDS, input[*i]) || ft_strchr(QUOTES, input[*i]))
					break;
				// Add character to the buffer
				buff[buff_len++] = input[*i];
				if (buff_len >= 1024)
				{
					printf("Minishell: buffer overflow\n");
					msh->exit_code = 1;
					return (tokens);
				}
				(*i)++;
			}
			// stops at BOUNDS or QUOTES
			if(input[*i] == ' ' || input[*i] == '\0' || ft_strchr(BOUNDS, input[*i])) // we append only if we find space or BOUNDS
			{
				(*i)--; // go back to avoid bound being skipped by main loop
				buff[buff_len] = '\0'; // Null-terminate only when we know e have to
				if (buff_len > 0)
				{
					append_token(&tokens, create_token(buff, ARG));
					buff_len = 0; // reset the len of the buff
					return(tokens);
				}
			}
		}
	}
	return(tokens);
}