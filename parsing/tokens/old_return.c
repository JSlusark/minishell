/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/12 13:35:20 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	collect_str(int *i, char *input, char quote, int *len)
{
	// printf("%c %c\n", input[*i], quote);
	while(input[*i] != '\0') // echo "hello""" does not print error
	{
		if(input[*i] == quote)
			(*i)++;

		else
		{
			if (input[*i] == '$' && quote == '"') // Expand variable only inside double quotes
			{
				char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";
				int j = *i + 1; // Start after the '$'
				while (input[j] && !ft_strchr(not_env, input[j]))
				{
					j++;
				}
				// Check if the substring matches "USER"
				if (ft_strncmp(&input[*i + 1], "USER", j - *i - 1) == 0 &&
					(size_t)(j - *i - 1) == ft_strlen("USER"))
				{
					printf("jjs"); // Replace with the actual expansion
					*len += 3;    // Add the length of "jjs" to the token length
				}
				else
				{
					// Print the variable name literally if no match
					while (*i < j)
					{
						// printf("%c", input[*i]);
						(*i)++;
						// (*len)++;
					}
				}
				*i = j; // Move *i past the variable name
			}
			else
			{
				// Print non-variable characters
				printf("%c", input[*i]);
				(*len)++; // <----- len is effed up when non existing env var
				(*i)++;
			}
		}

	}
}

bool	quote_closed(int i, char *input, char quote)
{
	int j = i;
	j++;
	while(input[j] && input[j] != quote && input[i] != '\0')
		j++;
	if(input[j] == quote)
		return(true);
	return(false);
}

t_tokens *return_tokens(char *input)
{
	int i = 0;
	char *invalid = ";#&,`*~\\";  // seen outside string also && $(..)
	char *bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	char *quotes = "\"'";  // anything inside quotes is considered an arg, for expansion we check if token is D STRING and if it has $ inside

	// t_tokens *tokens = NULL;


	while (input[i] != '\0')
	{
		// char buff[1024];
		int len = 0;
		int h = i;

		// CHECK INVALID
		while(ft_strchr(invalid, input[h])) //FTSTRCHR DOES NOT WORK AS I WANT TO
		{
			h++;
			if(input[h] == '\0' || ft_strchr(bounds, input[h])) // problem when followed by other invalid symbls
			{
				printf("Minishell: invalid token %c at input[%d]\n", input[i], i); // why wrong input
				return(NULL);
			}
			if(!ft_strchr(invalid, input[h]))
				break;
		}

		// CREATE ARGS
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0') // this grabs leters attached together as tokens, even when we have strings
		{
			if(ft_strchr(quotes, input[i]) && input[i] != '\0')
			{
				// CHECK QUOTEDARG
				if (!quote_closed(i, input, input[i]))
				{
					printf("Minishell: %c at input[%d] had no closure\n", input[i], i);
					return (NULL);
				}
				collect_str(&i, input, input[i], &len);
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
					printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
			}
			else
			{
				printf("%c", input[i]);
				i++;
				len++;
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
					printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
			}
		}
		// CHECK BOUNDS
		if(input[i] == '|')
		{
			int k = i + 1;
			if(input[k] != '\0' && input[k] == '|')
			{
				printf("||");
				printf(COLOR_YELLOW"<---- OPERATOR\n"COLOR_RESET);
				printf("Minishell: error || operator are just for bonus\n");
				return(NULL);
				i++;
			}
			else
			{
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- PIPE len 1\n"COLOR_RESET);
			}
		}
		if(input[i] == '>') // use a while to understand if >> ?
		{
			int j = i + 1;
			if(input[j] != '\0' && input[j] == '>')
			{
				printf(">>");
				printf(COLOR_YELLOW"<---- APPEND_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- IN_REDIR len 1\n"COLOR_RESET);
			}
		}
		if(input[i] == '<') // use a while to understand if >> ?
		{
			int y = i + 1;
			if(input[y] != '\0' && input[y] == '<')
			{
				printf("<<");
				printf(COLOR_YELLOW"<---- HEREDOC_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- OUT_REDIR len 1\n"COLOR_RESET);
			}
		}
		if(input[i] != '\0')
			i++;
	}
	return(NULL); // <- return error as this
}
