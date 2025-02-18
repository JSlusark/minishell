/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:50:00 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/18 13:51:30 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *duplicate_cmd(t_cmd *cmd)
{
    if (!cmd)
        return NULL;

    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;

    new_cmd->cmd = cmd->cmd ? strdup(cmd->cmd) : NULL;

    if (cmd->args)
    {
        int i;
        for (i = 0; cmd->args[i]; i++);
        new_cmd->args = malloc((i + 1) * sizeof(char *));
        if (!new_cmd->args)
        {
            free(new_cmd);
            return NULL;
        }
        for (i = 0; cmd->args[i]; i++)
            new_cmd->args[i] = strdup(cmd->args[i]);
        new_cmd->args[i] = NULL;
    }
    else
    {
        new_cmd->args = NULL;
    }

    new_cmd->option_n = cmd->option_n;
    return new_cmd;
}

t_redir *duplicate_redir(t_redir *redir)
{
    if (!redir)
        return NULL;

    t_redir *new_redir = malloc(sizeof(t_redir));
    if (!new_redir)
        return NULL;

    new_redir->prev = NULL;
    new_redir->type = redir->type;
    new_redir->redir_i = redir->redir_i;
    new_redir->target = redir->target ? strdup(redir->target) : NULL;
    new_redir->fd = redir->fd;
    new_redir->next = duplicate_redir(redir->next);

    if (new_redir->next)
        new_redir->next->prev = new_redir;

    return new_redir;
}

t_node_list *duplicate_node_list(t_node_list *node)
{
    if (!node)
        return NULL;

    t_node_list *new_node = malloc(sizeof(t_node_list));
    if (!new_node)
        return NULL;

    new_node->fd_in = node->fd_in;
    new_node->fd_out = node->fd_out;
    new_node->msh = node->msh; // Assuming msh is shared and not duplicated
    new_node->prev = NULL;
    new_node->cmd = duplicate_cmd(node->cmd);
    new_node->redir = duplicate_redir(node->redir);
    new_node->node_i = node->node_i;
    new_node->nodes_total = node->nodes_total;
    new_node->next = duplicate_node_list(node->next);

    if (new_node->next)
        new_node->next->prev = new_node;

    return new_node;
}