/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:44:47 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/30 17:54:57 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_eof(t_msh *msh)
{
	printf("exit\n");
	// i think we need to free msh and clearhisory
	//as we are exiting (no need to free nodes as there is no node creation)
	// might need to free the nodes if we invoke this when using heredoc?
	free_msh(msh);
	clear_history();
	exit(0); // returned exit code when we EOF and print echo $?
}
