/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:04:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/08 19:35:12 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int redir_out_append(t_node_list *node)
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
		return (-1);
	}
	if (dup2(node->redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		node->msh->exit_code = 1;
		close(node->redir->fd);
		return (-1);
	}
	close(node->redir->fd);
	return (0);
}

int redir_in(t_node_list *node)
{
	ft_dprintf("set redir IN\n");
			node->redir->fd = open(node->redir->target_name, O_RDONLY, 0777);
			if (node->redir->fd == -1)
			{
				perror("open");
				node->msh->exit_code = 1;
				return (-1); // <----- JESS: DOES NOT OVERWRITE EXIT CODE, WHY?
			}
			if (dup2(node->redir->fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				node->msh->exit_code = 1;
				close(node->redir->fd);
				return (-1);
			}
			close(node->redir->fd);
		return (0);
}

int set_redirection(t_node_list *node)
{
	int fd[2];
	char *doc;
	int click;

	click = 1;
	while (node->redir)
	{
		ft_dprintf("set_redirection\n");
		if(node->redir->type == HEREDOC)
		{
			if((doc = handle_heredoc(node)) != NULL)
				click = 0;
		}
		if (node->redir->type == REDIR_IN)
		{
			if(redir_in(node)== -1)
				return (-1);
		}
		if(node->redir->type == REDIR_OUT || node->redir->type == APPEND)
		{
			if (redir_out_append(node)== -1)
				return (-1);
		}
		node->redir = node->redir->next;
	}
	if (click == 0)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		write(fd[1], doc, ft_strlen(doc));
		close(fd[1]);
		close(fd[0]);
		free(doc);
	}
	return (0);
}