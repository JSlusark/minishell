/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:51 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/18 17:34:14 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// static void	free_arg_array(char **args)
// {
// 	int	i;

// 	i = 0;
// 	if (!args)
// 		return ;
// 	while (args[i])
// 	{
// 		free(args[i]);
// 		i++;
// 	}
// 	free(args);
// }

// void	free_redir_list(t_redir *head)
// {
// 	t_redir	*curr;
// 	t_redir	*temp;

// 	if (!head)
// 		return ;
// 	curr = head;
// 	while (curr)
// 	{
// 		free(curr->target);
// 		temp = curr->next;
// 		free(curr);
// 		curr = temp;
// 	}
// }

// void	free_cmd_struct(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return ;
// 	if (cmd->cmd)
// 		free(cmd->cmd);
// 	if (cmd->args)
// 		free_arg_array(cmd->args);
// 	free(cmd);
// }

// void	free_node_list(t_node_list *head)
// {
// 	t_node_list	*curr;
// 	t_node_list	*temp;

// 	if (!head)
// 		return ;
// 	curr = head;
// 	while (curr)
// 	{
// 		if (curr->cmd)
// 			free_cmd_struct (curr->cmd);
// 		if (curr->redir)
// 			free_redir_list (curr->redir);
// 		temp = curr->next;
// 		free(curr);
// 		curr = temp;
// 	}
// }


void free_redir_list(t_redir *head)
{
    t_redir *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->target)
            free(temp->target);
        free(temp);
    }
	free(head);
}

void free_cmd_struct(t_cmd *cmd)
{
    if (cmd)
    {
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        free(cmd);
    }
}

void free_msh(t_msh *msh)
{
    if (msh)
    {
        if (msh->ms_env)
        {
            for (int i = 0; msh->ms_env[i]; i++)
                free(msh->ms_env[i]);
            free(msh->ms_env);
        }
        if (msh->env_exp)
        {
            for (int i = 0; msh->env_exp[i]; i++)
                free(msh->env_exp[i]);
            free(msh->env_exp);
        }
        if (msh->home_path)
            free(msh->home_path);
        free(msh);
    }
}

void free_node_list(t_node_list *node_list)
{
    t_node_list *temp;

    while (node_list)
    {
        temp = node_list;
        node_list = node_list->next;
        if (temp->cmd)
            free_cmd_struct(temp->cmd);
        if (temp->redir)
            free_redir_list(temp->redir);
        free(temp);
    }
}