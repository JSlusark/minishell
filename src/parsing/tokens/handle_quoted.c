/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:41:21 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 19:02:43 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void quoted_buff(char *input, int *i, t_msh *msh, char *buff)
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
			// printf("Closing quote: %c at input[%d]\n", quote, *i);
			closure = true;
			break;
		}
		else if(input[*i] == '$' && quote == '"') // checks expansion, if it stops at " it should hit the quote conditional below
		{
			collect_expansion(input, i, buff, msh); // func to be used even in the non quote collection
			len = ft_strlen(buff); // Update the buffer length after expansion
			// printf("--> quoted_buff BUFF:%s\n", buff);
		}
		else
		{
			buff[len++] = input[*i]; // add characters to buff
			// (*i)--; // to avoid skipping $ later 😭 (not fond of doing all these movements, need to change)
		}

		if (len >= 1024) // if buff overflow
		{
			printf("Minishell: buffer overflow\n");
			msh->exit_code = 2;
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