/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_invalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:13 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 11:25:21 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool invalid_char(char *input, int i, t_tokens *tokens)
{
	char *invalid;				// seen outside string also && $(..)
	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
	int j;
	(void)tokens;

	invalid = ";#&,`*~\\";  // seen outside string also && $(..)
	bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	j = i;

	while(ft_strchr(invalid, input[j]))
	{
		j++;
		if(input[j] == '\0' || ft_strchr(bounds, input[j])) // problem when followed by other invalid symbls
		{
			printf("Minishell: invalid token %c at input[%d]\n", input[i], i); // why wrong input
			return(false);
		}
		if(!ft_strchr(invalid, input[j]))
			break;
	}
	return(true);
}