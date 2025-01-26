/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 19:04:06 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool empty_quoted(int *i, char *input) // I NEED ALSO TO MANAGE """""" CASE - should be easy
{
	// printf("last_quote_pos: %d c: %c\n", *i, input[*i]); // ""
	int prev_i = *i - 2; // character before the 2nd and 1st quote
	int next_i = *i + 1; // character after the 2nd quote
	// printf("prev_i: %d next_i: %d\n", prev_i, next_i);
	if((prev_i  < 0 || ft_strchr(BOUNDS, input[prev_i])) && (input[next_i] == '\0' || ft_strchr(BOUNDS, input[next_i])))
		return(true); // stops and appends a token with space (cases where "" is empty and delimited by spaces or start/end string delimiters)
	// could do a loop that checks until last quote if it is even? and acts the same way as  true up
	return(false);
}

bool stop_buffer(char *input, int *i, char *buff, t_msh *msh)
{
	if (msh->exit_code != 0)
		return true;

	if (input[*i + 1] == ' ' || input[*i + 1] == '\0' || ft_strchr(BOUNDS, input[*i + 1]))
	{
		if (ft_strlen(buff) > 0)
			return true;
		else if (empty_quoted(i, input))
			return true; // do not need to put empty buff, it will act already as i need like this
		return true;
	}

	(*i)++;
	return false;
}


void parse_string(char *input, int *i, t_msh *msh, char *buff)
{
	int len;

	while (!ft_strchr(BOUNDS, input[*i]) && input[*i] != '\0')
	{
		if (ft_strchr(QUOTES, input[*i])) // handles str in q
		{
			quoted_buff(input, i, msh, buff);
				// printf("--> parse string APPENDING BUFF:%s\n", buff);
			if (stop_buffer(input, i, buff, msh))
			{
				// printf("--> parse string APPENDING BUFF:%s\n", buff);
				return;
			}
			len = ft_strlen(buff);
		}
		else // handles c attached (will add to buffer if close to "")
		{
			unquoted_buff(input, i, msh, buff);
			len = ft_strlen(buff);
			if (input[*i] == '\0' || ft_strchr(BOUNDS, input[*i]))
			{
				buff[len] = '\0';
				(*i)--; // added this to go back on last character of the token so that it moves forward in the main loop
				if (len > 0)
					return;
			}
		}
	}
}
