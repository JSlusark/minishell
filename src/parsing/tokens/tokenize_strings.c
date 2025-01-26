/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 16:36:59 by jslusark         ###   ########.fr       */
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
	// need to use collect $ buff here
	buff[len++] = input[*i];
	printf("BUFF: %s\n", buff);
	(*i)++;
	if (input[*i] == '\0' || ft_strchr(BOUNDS, input[*i]))
		buff[len] = '\0';
}

void collect_expansion(char *input, int *i, char *buff, t_msh *msh)
{
	char *not_env;
	int len;

	len = ft_strlen(buff);
	not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>,.`~ ";
	printf("collect expansion called:\n");
	printf("\t- char:%c\n\t- i:%d\n", input[*i], *i);
	(*i)++; // skips $, lands on next char to see exp
	printf("\t- char:%c\n\t- i:%d\n", input[*i], *i);

	if (ft_strchr(not_env, input[*i])) // if after $ there is not env
	{
		printf("HIT BOUND NO EXPANSION NEEDED\n");
		buff[len++] = '$'; // adds just $ and stays on the bound to process later in cond
		(*i)--; // to avoid skipping the last ch
		printf("\t- BUFF:%s\n", buff);
		return;
	}
	else if (input[*i] == '?')
	{
		printf("HIT EXIT, EXPANDING TO CODE\n");
		int j = 0; // Use a while loop instead of a for loo
		int exp_len;
		char *exp_exit;
		exp_exit = ft_itoa(msh->exit_code); // Convert exit code to string
		exp_len = strlen(exp_exit);
		(*i)++; // skips ? as it's expanded
		if (len + exp_len >= 1023) // Prevent buffer overflow
		{
			printf("Error: Buffer overflow during $? expansion\n");
			free(exp_exit);
			return;
		}
		while (j < exp_len) // copies exit code to buff
		{
			buff[len] = exp_exit[j];
			(len)++;
			j++;
		}
		printf("\t- BUFF:%s\n", buff);
		free(exp_exit); // Free the dynamically allocated exit code string
		(*i)--; // to avoid skipping the last ch
		return;
	}
	else
	{
		int end;
		end = *i;
		char *var_name; // Extract the variable name
		char *expansion; // Extract the variable name
		while (input[end] && !ft_strchr(not_env, input[end])) // OR INPUT[end] is not nulL!!!
			end++;
		var_name = ft_substr(input, *i, end - (*i)); // Extract the variable name $USER
		if (!var_name)
		{
			printf("Error: Failed to allocate memory for variable name\n");
			msh->exit_code = 2;
			return;
		}
		expansion = find_envar(var_name, msh->ms_env);
		free(var_name); // Free the temporary variable name
		if (expansion) // WHAT IF EX IS NOT EXISTIG
		{
			int exp_len = strlen(expansion);
			if (len + exp_len >= 1023) // Prevent buffer overflow
			{
				printf("Error: Buffer overflow during variable expansion\n");
				free(expansion);
				return;
			}
			int k = 0; // start of expansion string
			while (k < exp_len) // Copies the expansion into the buffer
			{
				buff[len] = expansion[k];
				(len)++;
				k++;
			}
			free(expansion); // Frees the copied expansion
			// *i = end - 1 ; // Move *i to the last character of the variable name
		}
		else
		{
			buff[len] = ' ';
			// *i = end - 1 ; // Move *i to the last character of the variable name
		}
		*i = end - 1 ; // Move *i to the last character of the variable name
		printf(COLOR_RED"char landed: %c\n"COLOR_RESET, input[*i]);
	}
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
	while (input[*i] != '\0') // collect buffer until end
	{
		if (input[*i] == quote) // or until closed quote
		{
			printf("Closing quote: %c at input[%d]\n", quote, *i);
			closure = true;
			break;
		}
		else if(input[*i] == '$' && quote == '"') // checks expansion, if it stops at " it should hit the quote conditional below
		{
			collect_expansion(input, i, buff, msh); // func to be used even in the non quote collection
			len = ft_strlen(buff); // Update the buffer length after expansion
			printf("--> quote_buff BUFF:%s\n", buff);
		}
		else
		{
			buff[len++] = input[*i]; // add characters to buff
			// (*i)--; // to avoid skipping $ later 😭 (not fond of doing all these movements, need to change)
		}

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
