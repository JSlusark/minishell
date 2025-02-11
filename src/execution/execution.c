/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 23:54:49 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/11 02:10:02 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_execution(t_node_list *node_list, t_exec *exec,
	int **pipes, int node_amount)
{
	reset_in_out(exec->stds_cpy);
	exec->exit_code = close_wait_free(pipes, node_amount, exec->last_pid);
	if (exec->exit_code == 255)
		node_list->msh->exit_code = 1;
	else if (exec->exit_code == 13)
		node_list->msh->exit_code = 0;
	else
		node_list->msh->exit_code = exec->exit_code;
}

int	exec_child(t_node_list *node, int **pipes, int node_amount, int position)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = fork();
	run_signals(2, node->msh);
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (pipes)
			set_pipe_ends(pipes, position, node_amount - 1);
		if (node->redir)
		{
			if (set_redirection(node) == -1)
				exit(-1);
		}
		if (node->cmd != NULL)
			exec_cmd(node, pipes, node_amount);
		exit(0);
	}
	return (pid);
}

int	single_node(t_node_list *head, int **pipes, int node_amount, int *stds_cpy)
{
	if (node_amount == 1 && (find_builtin(head) == 0))
	{
		if (head->redir)
		{
			if (set_redirection(head) == -1)
			{
				free_pipes(pipes, node_amount - 1);
				reset_in_out(stds_cpy);
				return (-1);
			}
		}
		if ((exec_builtin(head)) == 0)
		{
			free_pipes(pipes, node_amount - 1);
			reset_in_out(stds_cpy);
			return (0);
		}
	}
	return (1);
}

int	set_and_init(t_node_list *node_list, t_exec **exec, 
	int *node_amount, int ***pipes)
{
	*exec = malloc(sizeof(t_exec));
	if (!*exec)
		return (node_list->msh->exit_code = 1);
	*node_amount = count_nodes(node_list);
	(*exec)->stds_cpy[0] = dup(STDIN_FILENO);
	(*exec)->stds_cpy[1] = dup(STDOUT_FILENO);
	if ((*exec)->stds_cpy[0] == -1 || (*exec)->stds_cpy[1] == -1)
		return (node_list->msh->exit_code = 1);
	if (*node_amount > 1)
	{
		*pipes = pipe_init(*node_amount - 1);
		if (*pipes == NULL)
			return (node_list->msh->exit_code = 1);
	}
	else
		*pipes = NULL;
	return (0);
}

void	exec_nodes(t_node_list *node_list)
{
	int			node_amount;
	t_node_list	*head;
	int			**pipes;
	int			i;
	t_exec		*exec;

	exec = NULL;
	if (set_and_init(node_list, &exec, &node_amount, &pipes) == 1)
		return ;
	i = 0;
	head = node_list;
	while (head)
	{
		exec->exit_code = single_node(head, pipes, node_amount, exec->stds_cpy);
		if (exec->exit_code == -1 || exec->exit_code == 0)
			return ;
		exec->last_pid = exec_child(head, pipes, node_amount, i);
		if (exec->last_pid == -1)
			break ;
		head = head->next;
		i++;
	}
	close_execution(node_list, exec, pipes, node_amount);
}
