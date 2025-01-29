/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:37:41 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/29 15:51:12 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OLD FROM STEFANO
#include "../../../include/minishell.h"

int	handle_pwd(t_node_list	*node)
{
	char *cwd;

	cwd = getcwd(NULL, 0); // gets current working directory and allocates the necessary memory dynamically
	if (cwd != NULL)
	{
		write(node->fd_out, cwd, ft_strlen(cwd));
		write(node->fd_out, "\n", 1); // Write a newline at the end
		free(cwd); // Free allocated memory
		return (0);
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
			node->msh->exit_code = 1; // Generic error
			return (1);
		// }
	}

}
