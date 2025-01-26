/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nonquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:55:56 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 22:22:07 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
void unquoted_buff(char *input, int *i, t_msh *msh, char *buff)
{
	int len;
	(void)msh;

	len = ft_strlen(buff);
	if(input[*i] == '$') // checks expansion, if it stops at " it should hit the quote conditional below
	{
		collect_expansion(input, i, buff, msh); // func to be used even in the non quote collection
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
