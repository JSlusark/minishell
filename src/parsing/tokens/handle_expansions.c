/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:40:17 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 11:40:34 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *find_envar(char *var, char **env) // finds only the var, does not expand
{
	int i;
	char *var_content;
	i = 0;
	var_content = NULL;
	while (env[i])
	{
		if (strncmp(env[i], var, strlen(var)) == 0 && env[i][strlen(var)] == '=')
		{
			var_content = env[i] + strlen(var) + 1;
			break;
		}
		i++;
	}
	if (!env[i]) // if var does not exists it expans to null
		return (NULL);
	return ft_strdup(var_content);
}