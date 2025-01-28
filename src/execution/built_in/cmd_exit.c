/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:54 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/28 11:23:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int check_exit(t_node_list *node, t_msh *msh, char **av)
{
	long long   exit_code;
	int         i;
	(void)node;

	if(av[1])
	{
		// printf (" too many arguments\n");
        write(2, "exit: too many arguments\n", 25);
		msh->exit_code = 1;
		return(1);
	}
	i = 0;
	while (av[0][i] == ' ')
		i++;
	if (av[0][i] == '+' || av[0][i] == '-')
		i++;
	if (!ft_isdigit(av[0][i]))
	{
		// printf ("exit: %s isn't numeric argument\n", av);
		// printf (" numeric argument required\n");
        write(2, "exit: numeric argument required\n", 32);
		msh->exit_code = 2;/// <---------- it is 2 on linux (255 on mac?)
		return (1);
	}
	exit_code = ft_atoll(av[0]);
	if (ft_isllong(av[0]) != 0 || exit_code < LLONG_MIN || exit_code > LLONG_MAX)
	{
		// printf ("exit: %s isn't numeric argument\n", av[0]);
        write(2, "exit: numeric argument required\n", 32);
		msh->exit_code = 255;
		return (1);
	}
	msh->exit_code = exit_code % 256;
	if (msh->exit_code < 0)
		msh->exit_code += 256;
	return (0);
}

int    exec_exit(t_node_list	*node) //char *av will become a char **av
										//once the cmd struct is updated to include char **args
{
	int exit_code;

	// printf("Exiting minishell...\n");
	if (node->cmd->args)
		exit_code = check_exit(node, node->msh, node->cmd->args); //av will become av[0]
	exit_code = node->msh->exit_code; // <--- jess: conserviamo l'esxit code aggiornato qua per non cancellarlo con free_msh prima dell'exit
	clear_history();
	free_msh(node->msh); // <----------- unico edit from JESS: l'ho messo per liberare la memoria correttamente da msh prima di uscire ed evutare che ci sia della memoria "still rechable" per via degli envar in msh
	free_node_list(node);
	exit (exit_code); //
}
