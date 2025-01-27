/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nonquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:55:56 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 15:57:06 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
void unquoted_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	(void)msh;
	int y;

	y = *i + 1;
	len = ft_strlen(buff);
	if(input[*i] == '$') // checks expansion, if it stops at " it should hit the quote conditional below
	{
		if(ft_strchr(QUOTES, input[y]) && input[y] != '\0')
		{
			(*i)++; // skips $, lands on next char to see exp
			return;
		}
		collect_expansion(input, i, buff, msh); // func to be used even in the non quote collection
		// if buff is null it should not append as it does with quotes  $NOTREAL ciao (ciao not found)
		len = ft_strlen(buff); // Update the buffer length after expansion
		(*i)++; // to skip R
		// printf("--> quoted_buff BUFF:%s\n", buff);
	}
	else
	{
		buff[len++] = input[*i];
		// printf("BUFF: %s\n", buff);
		(*i)++;
	}
	if (input[*i] == '\0' || ft_strchr(BOUNDS, input[*i]))
		buff[len] = '\0';
}
