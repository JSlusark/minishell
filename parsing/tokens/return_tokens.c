/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 10:34:54 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	collect_str(int *i, char *input, char quote)
{
	(*i)++;
	// printf("i %d char %c\n", *i, input[*i]);
	while(input[*i] && input[*i] != quote) // echo "hello""" does not print error
	{
		write(1, &input[*i],1);
		(*i)++;
	}
	if(input[*i] == quote)
		(*i)++;
	write(1, "\n",1);
}

bool	quote_closed(int i, char *input, char quote)
{
	int j = i;
	j++;
	// printf("j %d char %c\n", i, input[j]);
	while(input[j] && input[j] != quote)
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
			printf("\nout: %c\n", input[i]);
		if(input[i] == '<') // same?
			printf("\nin: %c\n", input[i]);
		if(input[i] != '\0')
			i++;
	}
	printf("\n");
	return(NULL); // <- return error as this
}




/*






*/
