/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:44:47 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/30 18:32:36 by jslusark         ###   ########.fr       */
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

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n"); // Move to a new line
	rl_on_new_line(); // Tell readline we're on a new line
	rl_replace_line("", 0); // Clear the current input
	rl_redisplay(); // Redisplay the prompt
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint); // it shoudl also change the prev exit status to 1, prints ^C and unsure if ok
	signal(SIGQUIT, handle_sigquit); // doesn't work well
}
