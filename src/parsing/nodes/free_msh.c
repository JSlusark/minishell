/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:32:30 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 14:41:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_msh(t_msh *msh)
{
	int	i;

	if (!msh)
		return ;
	if (msh->ms_env)
	{
		i = 0;
		while (msh->ms_env[i])
		{
			free (msh->ms_env[i]);
			i++;
		}
		free(msh->ms_env);
	}
	if (msh->env_exp)
	{
		i = 0;
		while (msh->env_exp[i])
		{
			free (msh->env_exp[i]);
			i++;
		}
		free(msh->env_exp);
	}
	free(msh);
}
