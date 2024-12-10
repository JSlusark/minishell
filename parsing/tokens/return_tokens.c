/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 15:33:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	collect_str(int *i, char *input, char quote)
{
	if(input[*i] != '\0')
		(*i)++;
	while(input[*i] != '\0' && input[*i] != quote) // echo "hello""" does not print error
	{
		printf("%c", input[*i]);
		(*i)++;
	}
	if(input[*i] == quote && input[*i] != '\0')
		(*i)++;
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

t_token_list *return_tokens(char *input)
{
	int i = 0;
	// file abs and rel path we check after during exec
	// env var - we check during exec if in a double_s
	// env var - shall we do the same if out of the string? can be seen as an arg first?
	// invalid tokens.. unsure if needed to to give it a type be fair?
	// char *invalid = ";#&,`*~";  // seen outside string also && $(..)
	char *bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	char *quotes = "\"'";  // anything inside quotes is considered an arg, for expansion we check if token is D STRING and if it has $ inside

	while (input[i] != '\0')
	{
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0')
		{
			if(ft_strchr(quotes, input[i]) && input[i] != '\0')
			{
				// CHECK QUOTEDARG
				if (!quote_closed(i, input, input[i]))
				{
					printf("Minishell: %c at input[%d] had no closure\n", input[i], i);
					return (NULL);
				}
				collect_str(&i, input, input[i]);
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
					printf(COLOR_YELLOW" <---- ARG (parsing assigns later as cmd, arg or file)\n"COLOR_RESET);
			}
			else
			{
				printf("%c", input[i]);
				i++;
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
					printf(COLOR_YELLOW" <---- ARG (parsing assigns later as cmd, arg or file)\n"COLOR_RESET);
			}
		}
		// if(ft_strchr(invalid, input[i])) // <- says invalid
		// {
		// 	printf("\nMinishell: invalid token %c at input[%d]\n", input[i], i);
		// 	return(NULL);
		// }
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
				printf(COLOR_YELLOW"<---- PIPE\n"COLOR_RESET);
			}
		}
		if(input[i] == '>') // use a while to understand if >> ?
		{
			int j = i + 1;
			if(input[j] != '\0' && input[j] == '>')
			{
				printf(">>");
				printf(COLOR_YELLOW"<---- APPEND_REDIR\n"COLOR_RESET);
				i++;
			}
			else
			{
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- IN_REDIR\n"COLOR_RESET);
			}
		}
		if(input[i] == '<') // use a while to understand if >> ?
		{
			int y = i + 1;
			if(input[y] != '\0' && input[y] == '<')
			{
				printf("<<");
				printf(COLOR_YELLOW"<---- HEREDOC_REDIR\n"COLOR_RESET);
				i++;
			}
			else
			{
				printf("\n%c", input[i]);
				printf(COLOR_YELLOW"<---- OUT_REDIR\n"COLOR_RESET);
			}
		}
		if(input[i] != '\0')
		{
			// printf("\n");
			i++;
		}
	}
	// printf("\n");
	return(NULL); // <- return error as this
}
