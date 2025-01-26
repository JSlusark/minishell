/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:41:21 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 21:52:04 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool buffer_overflow(int len, t_msh *msh)
{
	if (len >= 1024)
	{
		printf("Minishell: buffer overflow\n");
		msh->exit_code = 2;
		return true;
	}
	return false;
}

bool unclosed_quote(char *input, int *i, t_msh *msh, bool *closure)
{
	if (input[*i] == '\0' && !(*closure)) // Handle unclosed quotes
	{
		msh->exit_code = 2;
		printf("Minishell: quote at input[%d] had no closure\n", *i);
		return(true);
	}
	return(false);
}
bool closed_quote(char *input,int *i, char quote, bool *closure)
{
	(void)closure;
	*closure = false;
		if (input[*i] == quote) // or until closed quote
		{
			*closure = true;
			// (*i)++; // we skip the closed quote
			return(true);
		}
		return(false);
}

void quoted_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	bool closure;
	char quote;

	quote = input[*i];
	(*i)++; // Skip the opening quote
	while (input[*i] != '\0') // collect buffer until end
	{
		len = ft_strlen(buff); // if buff is null strlen is 0, if it contains stuff it will be added after
		if (closed_quote(input, i, quote, &closure)) // or until closed quote
			break;
		else if(input[*i] == '$' && quote == '"') // checks expansion, if it stops at " it should hit the quote conditional below
			collect_expansion(input, i, buff, msh); // func to be used even in the non quote collection
		else
			buff[len++] = input[*i]; // add characters to buff
		if (buffer_overflow(len, msh)) // Check buffer overflow
			return;
		(*i)++;
	}
	if(unclosed_quote(input, i, msh, &closure))
		return;
	buff[len] = '\0'; // Null-terminate only when we know e have to
}
