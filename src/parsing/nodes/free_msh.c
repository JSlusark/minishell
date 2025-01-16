/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:32:30 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/16 15:49:04 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// msh and what it stores needs to be freed before we exit the program
// I do not know if freeing what is inside will affect any type of data we need after we exit from minishell (i think not)
// NOTE PER EXECUTION BRANCH:
// aggiunto in cmd_exit.c(l:51)
// aggiunto in main.c(l:70)

void free_msh(t_msh *msh)
{
	if (!msh)
		return;
	if (msh->ms_env)
	{
		int i = 0;
		while (msh->ms_env[i])
		{
			free(msh->ms_env[i]); // freeing each char env var to avoid data is stil reachable after exit
			i++;
		}
		free(msh->ms_env); // freeing the environment variable array container
	}
	free(msh); //  freeing the msh struct itself (IMPORTANT: CHECK IF ERROR COSE FOR EXIT IS AFFECTED)
}