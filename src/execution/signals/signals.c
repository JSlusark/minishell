/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:44:47 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/04 19:42:09 by jslusark         ###   ########.fr       */
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

void	handle_sigquit(int sig)
{
	g_sig = sig; // SIGQUIT
	// printf("Handle sigquit: %d\n", sig); // 3
	// printf("\b\b  \b\b"); // Remove `^\\` if it appears - probablt it's unneded
	rl_on_new_line();
	rl_redisplay();


	// if (isatty(STDIN_FILENO)) // Ignore SIGQUIT in interactive mode
	// 	return;
	// g_sig = sig;
	// write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = sig; // SIGINT
	// printf("Handle signint: %d\n", sig); //2
	// printf("\n"); // Move to a new line
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); // Redisplay the prompt //<------------------------ this redisplays twice when used ^c with cat
}

void	setup_signals(void)
{
	struct termios term;

	// Disables `^C` from being displayed, i can use the functions written below but unsure if i can use termios.h
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL; // Disables keys to appear in prompt as input
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	signal(SIGINT, handle_sigint); // it shoudl also change the prev exit status to 1, prints ^C and unsure if ok
	signal(SIGQUIT, handle_sigquit); // doesn't work well
}
