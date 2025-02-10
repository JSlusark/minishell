/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:59:25 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 21:43:46 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	store_home(char **env, t_msh *msh)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "HOME=", 5) == 0)
		{
			msh->home_path = strdup(env[i] + 5);
			if (!msh->home_path)
				return ;
			return ;
		}
		i++;
	}
}
