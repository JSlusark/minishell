/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:19:56 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/29 18:00:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_wait_free(int **pipes, int node_amount)
{
    if (pipes)
    {
        close_pipes(pipes, node_amount - 1); // Close all pipe ends in the parent process
    }
	    for (int j = 0; j < node_amount; j++) {
        wait(NULL);
    }
    if (pipes)
    {
        free_pipes(pipes, node_amount - 1); // Free allocated memory for pipes
	}
}

void	print_exec(t_node_list	*node)
{
	if(node->cmd == NULL)
		return ;
	if(strcmp(node->cmd->cmd, "cd") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < CD > BUILT-IN...\n\n"COLOR_RESET);
	}
	else if (strcmp(node->cmd->cmd, "env") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < ENV > BUILT-IN...\n\n"COLOR_RESET);
	}
	else if(strcmp(node->cmd->cmd, "echo") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < ECHO > BUILT-IN...\n\n"COLOR_RESET);
	}
	else if(strcmp(node->cmd->cmd, "exit") == 0)
	{
		// printf(COLOR_GREEN"Minishell> "COLOR_RESET); // <-- era stato rimosso prima, non so se era voluto
		// printf("Exiting minishell...\n");
		//why free_node_list, clear history and exit 0 where removed?
	}
	else if(strcmp(node->cmd->cmd, "export") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < EXPORT > BUILT-IN...\n\n"COLOR_RESET);
	}
	else if(strcmp(node->cmd->cmd, "pwd") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < PWD > BUILT-IN...\n\n"COLOR_RESET);
	}
	else if(strcmp(node->cmd->cmd, "unset") == 0)
	{
		// printf(COLOR_YELLOW"\nEXECUTING < UNSET > BUILT-IN...\n\n"COLOR_RESET);
	}
	else
	{
		// printf(COLOR_YELLOW"\nSEARCHING FOR /usr/bin/%s binary data AND EXECUTING..\n"COLOR_RESET, node->cmd->cmd);
	}
}

int count_nodes(t_node_list	*node_list)
{
	int n = 0;
	while (node_list)
	{
		n++;
		node_list = node_list->next;
	}
	return(n);
}

int	find_ext_cmd(t_node_list *node)
{
	char *path;

	if((path = find_path(node->cmd->cmd, node->msh->ms_env)) == NULL)
		return (1);
	free(path);
	return (0);
}

int	find_builtin(t_node_list	*node)
{
	if(strcmp(node->cmd->cmd, "cd") == 0)
		return (0);
	else if (strcmp(node->cmd->cmd, "env") == 0)
		return (0);
	else if(strcmp(node->cmd->cmd, "echo") == 0)
		return (0);
	else if(strcmp(node->cmd->cmd, "exit") == 0)
		return (0);
	else if(strcmp(node->cmd->cmd, "export") == 0)
		return (0);
	else if(strcmp(node->cmd->cmd, "pwd") == 0)
		return (0);
	else if(strcmp(node->cmd->cmd, "unset") == 0)
		return (0);
	return (1);
}

int check_cmds(t_node_list *node_list)
{
	t_node_list *node;

	node = node_list;
	while (node)
	{
		if (node->cmd)
		{
			if (find_builtin(node) == 1 && find_ext_cmd(node) == 1)
			{
				// printf("%s: command not found\n", node_list->cmd->cmd);
				write(2, node->cmd->cmd, ft_strlen(node->cmd->cmd));
				write(2, " command not found\n", 19); // i test passano solo se usiamo write con lo standarderror
				node->msh->exit_code = 127;
				/* JESS : ho aggiunto l'exit code e ho scoperto delle cose che ti lascio qui
				exit code = 127 quando il cmd non e' found oppure se il cmd e' un file o directory non trovato (esempio test da 137 o 140 )
				exit code = 126 quando il cmd e' un file o una directory dove il permission e' denied

				quando il cmd e' una directory (non un file) l'exit code e' 126 (vedi test 133 e 136) */
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}
