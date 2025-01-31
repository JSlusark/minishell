/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:04:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/30 18:05:42 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include "../../../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void handle_heredoc(t_redir *redir)
{
    char *line; // stringa in buffer
    char *doc = NULL; // heredoc string
    int fd[2];
	char *temp;

    ft_dprintf("handle_heredoc\n");
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (strcmp(line, redir->target_name) == 0)
        {
            free(line);
            break;
        }
        if (doc == NULL)
        {
            doc = ft_strdup(line);
        }
        else
        {
        	temp = ft_strjoin(doc, line);
            free(doc);
            doc = temp;
        }
        temp = ft_strjoin(doc, "\n");
        free(doc);
        doc = temp;
        free(line);
    }
	if (doc)
		write(fd[1], doc, strlen(doc));
    close(fd[1]);
    free(doc);
    if (dup2(fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd[0]);
        return;
    }
    close(fd[0]);
}

void set_redirection(t_node_list *node)
{
    while (node->redir)
    {
        ft_dprintf("set_redirection\n");
        if (node->redir->type == REDIR_IN)
        {   
            ft_dprintf("set redir IN\n");
            node->redir->fd = open(node->redir->target_name, O_RDONLY, 0777);
            if (node->redir->fd == -1)
            {
                perror("open");
                node->msh->exit_code = 1;
                return;
            }
            if (dup2(node->redir->fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                node->msh->exit_code = 1;
                close(node->redir->fd);
                return;
            }
            close(node->redir->fd);
        }
        if(node->redir->type == REDIR_OUT || node->redir->type == APPEND)
        {
            ft_dprintf("set redir OUT\n");
            if(node->redir->type == REDIR_OUT)
            node->redir->fd = open(node->redir->target_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            else if(node->redir->type == APPEND)
                node->redir->fd = open(node->redir->target_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
            if (node->redir->fd == -1)
            {
                perror("open");
                node->msh->exit_code = 1;
                return;
            }
            if (dup2(node->redir->fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                node->msh->exit_code = 1;
                close(node->redir->fd);
                return;
            }
            close(node->redir->fd);
        }
        if(node->redir->type == HEREDOC)
            handle_heredoc(node->redir);
        node->redir = node->redir->next;
    }
}