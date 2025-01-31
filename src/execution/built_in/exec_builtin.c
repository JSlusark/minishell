/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:25:47 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/31 12:29:21 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int 	exec_builtin(t_node_list	*node_list)
{
	int exit;

	exit = 1;
	if (!node_list->cmd)
		return (exit);
	if ((exit = strcmp(node_list->cmd->cmd, "echo")) == 0)
	exit = handle_echo(node_list);
	else if ((exit = strcmp(node_list->cmd->cmd, "cd")) == 0)
		printf("handle cd\n");//handle_cd(node->msh->ms_env);
	else if ((exit = strcmp(node_list->cmd->cmd, "pwd")) == 0)
		handle_pwd(node_list);
	else if ((exit = strcmp(node_list->cmd->cmd, "unset")) == 0)
		exec_unset(node_list->cmd->args, node_list);
	else if ((exit = strcmp(node_list->cmd->cmd, "env")) == 0)
		handle_env(node_list);
	else if ((exit = strcmp(node_list->cmd->cmd, "exit")) == 0)
		exec_exit(node_list);
	else if ((exit = strcmp(node_list->cmd->cmd, "export")) == 0)
		exec_export(node_list->cmd->args, node_list);
	return (exit);
}
