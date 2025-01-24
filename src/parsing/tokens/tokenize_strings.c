/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 22:31:41 by jslusark         ###   ########.fr       */
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


void quote_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	bool closure;
	char quote;


	len = ft_strlen(buff); // if buff is null strlen is 0, if it contains stuff it will be added after
	printf(COLOR_CYAN"START OF QUOTE STRING - "COLOR_RESET);
	printf("input[%d]: %c\n", *i, input[*i]);
	closure = false;
	quote = input[*i];
	// printf("Found quote: %c at input[%d]\n", quote, *i);
	(*i)++; // Skip the opening quote
	if(input[*i] == '\0') // if first quote followed by \0 error
	{
		msh->exit_code = 2;
		printf("Minishell: %c at input[%d] had no closure\n", quote, *i);
		return;
	}
	// int len = 0;
	while (input[*i] != '\0') // collect buffer until end
	{
		if (input[*i] == quote) // or until closed quote
		{
			// printf("Closing quote: %c at input[%d]\n", quote, *i);
			closure = true;
			break;
		}
		buff[len++] = input[*i]; // add characters to buff
		if (len >= 1024) // if buff overflow
		{
			printf("Minishell: buffer overflow\n");
			msh->exit_code = 1;
			return;
		}
		(*i)++;
	}
	// i stops at \0 or quote
	if(input[*i] == '\0' && !closure) // if not closed  and stops at null error
	{
		msh->exit_code = 2;
		printf("Minishell: %c at input[%d] had no closure\n", quote, *i);
		return;
	}
	buff[len] = '\0'; // Null-terminate only when we know e have to
}



t_tokens *parse_string(char *input, int *i, t_msh *msh, t_tokens *tokens)
{
	char buff[1024];
	int len;

	len = 0;
	memset(buff, 0, sizeof(buff));
	while (!ft_strchr(BOUNDS, input[*i]) && input[*i] != '\0')
	{
		if (ft_strchr(QUOTES, input[*i])) // handles str in q
		{
			quote_buff(input, i, msh, buff);
			if(msh->exit_code != 0)
				return(tokens);
			if(input[*i + 1] == ' ' || input[*i + 1] == '\0' || ft_strchr(BOUNDS, input[*i + 1])) // we append only if we find space or BOUNDS
			{
				if (ft_strlen(buff) > 0)
					append_token(&tokens, create_token(buff, ARG)); // free buff?
				else if(check_empty_string(i, input)) // if empty string is delimited by spaces or delimiters returns
				{
					*buff = ' ';
					append_token(&tokens, create_token(buff, ARG));
					// free buff?
				}
				return(tokens); // last i is on last QUOTE
			}
			(*i)++; // skip the ending quote only if we have to continue because no space or BOUNDS found
			len = ft_strlen(buff);
		}
		else // handles c attached (will add to buffer if close to "")
		{
			buff[len++] = input[*i];
			(*i)++;
			if (input[*i] == '\0' || ft_strchr(BOUNDS, input[*i]))
			{
				buff[len] = '\0';
				if (len > 0)
					append_token(&tokens, create_token(buff, ARG));
				// free buff?
			}
		}
	}
	return(tokens);
}