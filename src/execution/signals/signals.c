/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:44:47 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/05 20:09:07 by jslusark         ###   ########.fr       */
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
	// exit(msh->exit_code); // Preserve last exit code when exiting
}
void	restore_prompt(int sig)
{
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_sig = SIGINT;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_sig = SIGQUIT;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	run_signals(int sig, t_msh *msh)
{
	(void) msh;
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
		// printf("SIGINT exit %d\n", msh->exit_code);
	}
	else if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
		// printf("SIGQUIT exit: %d\n", msh->exit_code);
	}
}