/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/25 18:30:21 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_empty_string(int *i, char *input) // I NEED ALSO TO MANAGE """""" CASE - should be easy
{
	printf("last_quote_pos: %d c: %c\n", *i, input[*i]); // ""
	int prev_i = *i - 2; // character before the 2nd and 1st quote
	int next_i = *i + 1; // character after the 2nd quote
	printf("prev_i: %d next_i: %d\n", prev_i, next_i);
	if((prev_i  < 0 || ft_strchr(BOUNDS, input[prev_i])) && (input[next_i] == '\0' || ft_strchr(BOUNDS, input[next_i])))
		return(true); // stops and appends a token with space (cases where "" is empty and delimited by spaces or start/end string delimiters)
	// could do a loop that checks until last quote if it is even? and acts the same way as  true up
	return(false);
}

void unquoted_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	(void)msh;

	len = ft_strlen(buff);
	buff[len++] = input[*i];
	printf("BUFF: %s\n", buff);
	(*i)++;
	if (input[*i] == '\0' || ft_strchr(BOUNDS, input[*i]))
		buff[len] = '\0';
}


void quote_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	bool closure;
	char quote;


	len = ft_strlen(buff); // if buff is null strlen is 0, if it contains stuff it will be added after
	closure = false;
	quote = input[*i];
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

bool stop_buffer(char *input, int *i, char *buff, t_msh *msh)
{
	if (msh->exit_code != 0)
		return true;

	if (input[*i + 1] == ' ' || input[*i + 1] == '\0' || ft_strchr(BOUNDS, input[*i + 1]))
	{
		if (ft_strlen(buff) > 0)
			return true;
		else if (check_empty_string(i, input))
			*buff = ' ';
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
			quote_buff(input, i, msh, buff);
			if (stop_buffer(input, i, buff, msh))
				return;
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
