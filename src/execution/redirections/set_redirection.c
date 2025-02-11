/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:04:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/11 17:36:10 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// int	redir_out_append(t_node_list *node, t_redir *redir)
// {
// 	ft_dprintf("set redir OUT\n");
// 	if (redir->type == REDIR_OUT)
// 		redir->fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	else if (node->redir->type == APPEND)
// 		redir->fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (redir->fd == -1)
// 	{
// 		perror("open");
// 		node->msh->exit_code = 1;
// 		return (-1);
// 	}
// 	if (dup2(redir->fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		node->msh->exit_code = 1;
// 		close(redir->fd);
// 		return (-1);
// 	}
// 	close(redir->fd);
// 	return (0);
// }

// int	redir_in(t_node_list *node)
// {
// 	ft_dprintf("set redir IN\n");
// 	node->redir->fd = open(node->redir->target, O_RDONLY, 0777);
// 	if (node->redir->fd == -1)
// 	{
// 		perror("open");
// 		node->msh->exit_code = 1;
// 		return (-1);
// 	}
// 	if (dup2(node->redir->fd, STDIN_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		node->msh->exit_code = 1;
// 		close(node->redir->fd);
// 		return (-1);
// 	}
// 	close(node->redir->fd);
// 	return (0);
// }

// int	feed_heredoc_to_pipe(char *doc)
// {
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	write(fd[1], doc, ft_strlen(doc));
// 	close(fd[1]);
// 	close(fd[0]);
// 	return (0);
// }

// int	exec_redir(t_node_list *node)
// {
// 	if (node->redir->type == REDIR_IN)
// 	{
// 		if (redir_in(node) == -1)
// 			return (-1);
// 	}
// 	if (node->redir->type == REDIR_OUT || node->redir->type == APPEND)
// 	{
// 		if (redir_out_append(node, node->redir) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

// int	set_redirection(t_node_list *node)
// {
// 	while (node->redir)
// 	{
// 		if (exec_redir(node) == -1)
// 			return (-1);
// 		node->redir = node->redir->next;
// 	}
// 	return (0);
// }

// void	exec_heredoc(t_node_list *node)
// {
// 	char	*doc;

// 	doc = NULL;
// 	while (node)
// 	{
// 		while (node->redir)
// 		{
// 			if (node->redir->type == HEREDOC)
// 				doc = handle_heredoc(node);
// 			node->redir = node->redir->next;
// 		}
// 		node = node->next;
// 	}
// 	if (doc)
// 	{
// 		if (feed_heredoc_to_pipe(doc) == -1)
// 		{
// 			free(doc);
// 			perror("feed_heredoc_to_pipe");
// 		}
// 		free(doc);
// 	}
// }



int	redir_out_append(t_node_list *node, t_redir *redir)
{
	ft_dprintf("set redir OUT\n");
	if (redir->type == REDIR_OUT)
		redir->fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (node->redir->type == APPEND)
		redir->fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (redir->fd == -1)
	{
		perror("open");
		node->msh->exit_code = 1;
		return (-1);
	}
	if (dup2(redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		node->msh->exit_code = 1;
		close(redir->fd);
		return (-1);
	}
	close(redir->fd);
	return (0);
}

int	redir_in(t_node_list *node)
{
	ft_dprintf("set redir IN\n");
	node->redir->fd = open(node->redir->target, O_RDONLY, 0777);
	if (node->redir->fd == -1)
	{
		perror("open");
		node->msh->exit_code = 1;
		return (-1);
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

int	feed_heredoc_to_pipe(char *doc)
{
	int	fd[2];

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
	return (0);
}

int	exec_redir(t_node_list *node, char **doc, int *heredoc_buffer)
{
	if (node->redir->type == HEREDOC)
	{
		(*doc) = handle_heredoc(node);
		if ((*doc) != NULL)
			*heredoc_buffer = 0;
	}
	if (node->redir->type == REDIR_IN)
	{
		if (redir_in(node) == -1)
			return (-1);
	}
	if (node->redir->type == REDIR_OUT || node->redir->type == APPEND)
	{
		if (redir_out_append(node, node->redir) == -1)
			return (-1);
	}
	return (0);
}

int	set_redirection(t_node_list *node)
{
	char	*doc;
	int		heredoc_buffer;

	doc = NULL;
	heredoc_buffer = 1;
	while (node->redir)
	{
		if (exec_redir(node, &doc, &heredoc_buffer) == -1)
			return (-1);
		node->redir = node->redir->next;
	}
	if (heredoc_buffer == 0)
	{
		if (feed_heredoc_to_pipe(doc) == -1)
		{
			free(doc);
			return (-1);
		}
		free(doc);
	}
	return (0);
}