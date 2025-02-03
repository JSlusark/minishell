/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_invalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:13 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 15:04:07 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	invalid_char(char *input, int i)
{
	char	*invalid;
	char	*bounds;
	int		j;

	invalid = ";#&,`*~\\";
	bounds = "|>< ";
	j = i;
	if (ft_strchr(invalid, input[j]))
	{
		while (ft_strchr(invalid, input[j]) && input[j] != '\0')
			j++;
		if (ft_strchr(bounds, input[j]) || input[i] == '\0')
		{
			printf("Minishell: invalid token %c at input[%d]\n", input[i], i);
			return (true);
		}
	}
	return (false);
}
