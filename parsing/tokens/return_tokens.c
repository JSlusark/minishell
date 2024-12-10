/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 11:48:47 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	collect_str(int *i, char *input, char quote)
{
	if(input[*i] != '\0')
		(*i)++;
	// printf("i %d char %c\n", *i, input[*i]);
	while(input[*i] != '\0' && input[*i] != quote) // echo "hello""" does not print error
	{
		write(1, &input[*i],1);
		(*i)++;
	}
	if(input[*i] == quote && input[*i] != '\0')
		(*i)++;
	write(1, "\n",1);
}

bool	quote_closed(int i, char *input, char quote)
{
	int j = i;
	j++;
	printf("j %d char %c\n", i, input[j]);
	while(input[j] && input[j] != quote && input[i] != '\0')
		j++;
	if(input[j] == quote)
		return(true);
	return(false);
}

t_token_list *return_tokens(char *input)
{
	// t_token_list *head = NULL;      // Head of the linked list
	// t_token_list *current = NULL;   // Current node in the linked list
	int i;
	char *bounds; // used when we have stuff like echo|echo
	char *quotes; // used when we have stuff like echo|echo

	bounds = "|>< "; // not sure what to do with ec"h"o or echo"hello" , spaces could help me?
	quotes = "\"'";
	i = 0;
	while(input[i] != '\0')
	{
		if(ft_strchr(quotes, input[i]))
		{
			while(input[i] != '\0')
			{
				if(!quote_closed(i, input, input[i]))
				{
					printf("closure not found\n");
					return(NULL);
				}
					collect_str(&i, input, input[i]);
					// printf("we have a %c string\n", input[i]);
			}
				printf("last c after strcoll %c\n", input[i]);
				// if(ft_strchr(quotes, input[i]) && input[i] != '\0')
				// 	i++;
				// else
				// {
				// 	printf("%c", input[i]);
					i++;
				// }
		}
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0')
		{
			if(ft_strchr(quotes, input[i]) && input[i] != '\0')
				i++;
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




/*






*/
