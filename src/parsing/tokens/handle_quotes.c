/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:41:21 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 11:41:27 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
bool	quote_closed(int *i, char *input, char quote, int *last_quote)
{
	int j = *i;
	int quote_n = 0;
	char *bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	bool peek_quote = false;
	while(input[j] != '\0')
	{
		if(input[j] == quote)
		{
			*last_quote = j;
			quote_n++;
			// printf("quote_n %d\n", quote_n);
		}
		else if(ft_strchr(bounds, input[j])) // once we reach a bound we check the n of quotes and type of bounds
		{
			if(quote_n % 2 == 0 ) // we avoid including bounds in str
			{
				// printf(COLOR_GREEN"QUOTES CLOSED with last quote i %d\n"COLOR_RESET, *last_quote);
				return(true);
			}
			else if(quote_n %2 != 0 && input[j] == ' ') // we avoid continuing checking quotes that inclus | and redir
			{
				int k = j;
				while(input[k] != '\0') // check if there are other quotes in the string
				{
					// printf("-C: %c\n", input[k]);
					if(input[k] == quote)
					{
						peek_quote = true;
						break;
					}
					k++;
				}
				if(peek_quote == false)
				{
					printf("Minishell: %c at input[%d] had no closure\n", input[j], j);
					// printf(COLOR_RED"QUOTES UNCLOSED with last quote i %d\n", *last_quote);
					return(false);
				}
			}
		}
		j++;
	}
	if(quote_n % 2 != 0)
	{
		// printf(COLOR_RED"QUOTES UNCLOSED with last quote i %d\n", *last_quote);
		printf("Minishell: %c at input[%d] had no closure\n", input[j-1], j-1);
		return(false);
	}
	// printf(COLOR_GREEN"QUOTES CLOSED with last quote i %d\n"COLOR_RESET, *last_quote);
	return(true);
}