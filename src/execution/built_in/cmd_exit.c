/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:54 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 18:16:22 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int check_exit(t_msh *msh, char *av)
{
	long long   exit_code;
	int         i;

	i = 0;
	if (!av)
		return (0);
	while (av[i] == ' ')
		i++;
	if (av[i] == '+' || av[i] == '-')
		i++;
	if (!ft_isdigit(av[i]))
	{
		printf ("exit: %s isn't numeric argument\n", av);
		msh->exit_code = 255;
		return (1);
	}
	exit_code = ft_atoll(av);
	if (ft_isllong(av) != 0 || exit_code < LLONG_MIN || exit_code > LLONG_MAX)
	{
		printf ("exit: %s isn't numeric", av);
		msh->exit_code = 255;
		return (1);
	}
	msh->exit_code = exit_code % 256;
	if (msh->exit_code < 0)
		msh->exit_code += 256;
	return (0);
}

int    exec_exit(t_node_list	*node_l) //char *av will become a char **av
										//once the cmd struct is updated to include char **args
{
	int exit_code;

	printf("Exiting minishell...\n");
	// if (!av)
	//    exit_code = 0;
	//TO BE IMPLEMENTED ONCE THE CMD STRUCT IS UPDATED
	//exit_code = check_exit(msh, av[0]); //av will become av[0]
	// if (av[1] && i == 0)
	// {
	//     ft_printf ("exit: too many arguments\n");
	//     msh->exit_code = 1;
	//     return (1);
	// }
	// exit_code = 0; //node_l->msh->exit_code;
	exit_code = node_l->msh->exit_code; // <--- jess: conserviamo l'esxit code aggiornato qua per non cancellarlo con free_msh prima dell'exit
	clear_history();
	free_msh(node_l->msh); // <----------- unico edit from JESS: l'ho messo per liberare la memoria correttamente da msh prima di uscire ed evutare che ci sia della memoria "still rechable" per via degli envar in msh
	free_node_list(node_l);
	exit (exit_code); //
}