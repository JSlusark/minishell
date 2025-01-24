/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_invalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:13 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 19:05:29 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool invalid_char(char *input, int i)
{
	char *invalid;				// seen outside string also && $(..)
	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
	int j;

	invalid = ";#&,`*~\\";  // seen outside string also && $(..)
	bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	j = i;

	if(ft_strchr(invalid, input[j])) // if char is invalid
	{
		printf("YO\n");
		j++; // pass after the invalid
		if(ft_strchr(bounds, input[j]) || input[i] == '\0') // if next char is bound or end return error
		{
			printf("YO 2\n");
			return(true);
		}
		else
		{
			while(ft_strchr(invalid, input[j]) && input[j] != '\0') //skip all invalid if attached together
				j++;
			// we land on a character that is not invalid
			if(ft_strchr(bounds, input[j]) || input[i] == '\0') // if next char is bound or end return error
				return(true);
		}
	}
	return(false); // is not invalid so we process as a str
}