/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:37:41 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 17:57:30 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OLD FROM STEFANO
#include "../../../include/minishell.h"

void	exec_pwd(t_node_list	*node_l)
{
	char *cwd;

	cwd = getcwd(NULL, 0); // gets current working directory and allocates the necessary memory dynamically
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd); // Free the dynamically allocated memory
	}
	else // commented the other ifs as I am unsure if we have to do this
	{
		printf(COLOR_GREEN"Minishell> "COLOR_RESET);
		// if (errno == ERANGE)
		// {
		// 	printf("pwd: Buffer size too small\n");
		// 	node_l->msh->exit_code = 1;
		// }
		// else if (errno == EACCES)
		// {
		// 	printf("pwd: Permission denied\n");
		// 	node_l->msh->exit_code = 126;
		// }
		// else if (errno == ENOENT)
		// {
		// 	printf("pwd: Current directory is inaccessible or deleted\n");
		// 	node_l->msh->exit_code = 127;
		// }
		// else if (errno == ENOMEM)
		// {
		// 	printf("pwd: Insufficient memory to allocate path\n");
		// 	node_l->msh->exit_code = 1;
		// }
		// else
		// {
			perror("pwd");
			node_l->msh->exit_code = 1; // Generic error
		// }
	}

}