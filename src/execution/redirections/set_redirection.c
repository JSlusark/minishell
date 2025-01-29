/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:04:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/28 12:21:02 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void set_redirection(t_node_list *node)
{
    ft_dprintf("set_redirection\n");
    if (node->redir->type == REDIR_IN)
    {
        ft_dprintf("set redir IN\n");
        node->redir->fd = open(node->redir->target_name, O_RDONLY, 0777);
        if (node->redir->fd == -1)
        {
            perror("open");
            return;
        }
        if (dup2(node->redir->fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(node->redir->fd);
            return;
        }
        close(node->redir->fd);
    }
    if(node->redir->type == REDIR_OUT)
    {
        ft_dprintf("set redir OUT\n");
        node->redir->fd = open(node->redir->target_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (node->redir->fd == -1)
        {
            perror("open");
            return;
        }
        if (dup2(node->redir->fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            close(node->redir->fd);
            return;
        }
        close(node->redir->fd);
    }    
}