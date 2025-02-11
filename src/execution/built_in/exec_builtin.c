/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:25:47 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/11 14:51:25 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	exec_builtin_2(t_node_list *node_list)
{
	int	exit;

	exit = 1;
	if (strcmp(node_list->cmd->cmd, "unset") == 0)
	{
		exit = 0;
		exec_unset(node_list->cmd->args, node_list);
	}
	if (strcmp(node_list->cmd->cmd, "env") == 0)
	{
		exit = 0;
		handle_env(node_list);
	}
	else if (strcmp(node_list->cmd->cmd, "exit") == 0)
	{
		exit = 0;
		exec_exit(node_list);
	}
	else if (strcmp(node_list->cmd->cmd, "export") == 0)
	{
		exit = 0;
		exec_export(node_list->cmd->args, node_list);
	}
	return (exit);
}

int	exec_builtin(t_node_list	*node_list)
{
	int	exit;

	exit = 1;
	if (!node_list->cmd)
		return (exit);
	if ((strcmp(node_list->cmd->cmd, "echo")) == 0)
		exit = handle_echo(node_list);
	else if ((strcmp(node_list->cmd->cmd, "cd")) == 0)
	{
		exit = 0;
		exec_cd(node_list);
	}
	else if (strcmp(node_list->cmd->cmd, "pwd") == 0)
	{
		exit = 0;
		handle_pwd(node_list);
	}
	exit = exec_builtin_2(node_list);
	return (exit);
}
