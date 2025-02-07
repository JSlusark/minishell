/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:19:56 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/06 20:44:54 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_wait_free(int **pipes, int node_amount, int last_pid)
{
	int wstatus;
	int exit_code;
	int signal;
	int j;
	pid_t pid;

	signal = 0;
	wstatus = 0;
    if (pipes)
    {
        close_pipes(pipes, node_amount - 1); // Close all pipe ends in the parent process
    }
	//printf("last_pid: %d\n", last_pid);
	j = 0;
	while (j < node_amount) 
	{
		pid = waitpid(-1, &wstatus, 0);
		//printf("wait for pid: %d\n", pid);
		if(pid == last_pid)
		{
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
			{
				signal = WTERMSIG(wstatus);
				return (signal);
			}
		}
		j++;
    }
    if (pipes)
    {
        free_pipes(pipes, node_amount - 1); // Free allocated memory for pipes
	}
	return (exit_code);
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
	if (!node->cmd)
		return (1);
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
				printf("%s: command not found\n", node->cmd->cmd);
				node_list->msh->exit_code = 1;
				return (1);
			}			
		}
		node = node->next;
	}
	return (0);
}