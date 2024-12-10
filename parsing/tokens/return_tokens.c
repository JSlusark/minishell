/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 12:46:39 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	collect_str(int *i, char *input, char quote)
{
	if(input[*i] != '\0')
		(*i)++;
	// printf("i %d char %c\n", *i, input[*i]);
	// printf("string surrounded by %c: ", quote);
	while(input[*i] != '\0' && input[*i] != quote) // echo "hello""" does not print error
	{
		printf("%c", input[*i]);
		// write(1, &input[*i],1);
		(*i)++;
	}
	if(input[*i] == quote && input[*i] != '\0')
		(*i)++;
	// printf("\n");
}

bool	quote_closed(int i, char *input, char quote)
{
	int j = i;
	j++;
	// printf("j %d char %c\n", i, input[j]);
	while(input[j] && input[j] != quote && input[i] != '\0')
		j++;
	if(input[j] == quote)
		return(true);
	return(false);
}

t_token_list *return_tokens(char *input)
{
	int i = 0;
	char *bounds = "|>< "; // Chara
	char *quotes = "\"'";  // Quote characters

	while (input[i] != '\0')
	{
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0')
		{
			if(ft_strchr(quotes, input[i]) && input[i] != '\0')
			{
				// CHECK QUOTEDARG
				if (!quote_closed(i, input, input[i]))
				{
					printf("Minishhell: %c at index %d had no closure\n", input[i], i);
					return (NULL);
				}
				collect_str(&i, input, input[i]);
			}
			else
			{
				printf("%c", input[i]);
				i++;
			}
		}
		if(input[i] == '|')
			printf("\npipe: %c\n", input[i]);
		if(input[i] == '>') // use a while to understand if >> ?
		{
			int j = i + 1;
			if(input[j] != '\0' && input[j] == '>')
			{
				printf("\nappend: >>\n");
				i++;
			}
			else
				printf("\nin: %c\n", input[i]);
		}
		if(input[i] == '<') // use a while to understand if >> ?
		{
			int y = i + 1;
			if(input[y] != '\0' && input[y] == '<')
			{
				printf("\nheredoc: <<\n");
				i++;
			}
			else
				printf("\nout: %c\n", input[i]);
		}
		if(input[i] != '\0')
		{
			printf("\n");
			i++;
		}
	}
	printf("\n");
	return(NULL); // <- return error as this
}
