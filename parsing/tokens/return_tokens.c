/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 10:20:34 by jslusark         ###   ########.fr       */
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
	while(input[i])
	{
		// t_token_list *new_token = malloc(sizeof(t_token_list));
		// if(input[i] == '"' || input[i] == '\'')
		// {
		// 	if(!quote_closed(i, input, input[i]))
		// 	{
		// 		printf("closure not found\n");
		// 		return(NULL);
		// 	}
		// 	collect_str(&i, input, input[i]);
		// 	// printf("we have a %c string\n", input[i]);
		// }
		// else
		// {
			// write(1, &input[i], 1);
			// write(1, "\n", 1);
		// }
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0' && input[i])
		{
			if(ft_strchr(quotes, input[i]))
				i++;
			else
			{
				printf("%c", input[i]);
				i++;
			}
		}

		printf("\n%c\n", input[i]);
		i++;
	}
	return(NULL); // <- return error as this
}




/*






*/
