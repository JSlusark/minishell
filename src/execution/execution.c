/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 23:54:49 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/19 12:19:49 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_execution(t_exec *exec, int **pipes)
{
	reset_in_out(exec->stds_cpy);
	exec->exit_code = close_wait_free(pipes, exec->node_amount, exec->last_pid);
	if (exec->exit_code == 255)
		exec->msh->exit_code = 1;
	else if (exec->exit_code == 13)
		exec->msh->exit_code = 0;
	else
		exec->msh->exit_code = exec->exit_code;
}

int	exec_child(t_node_list *node, int **pipes, t_exec *exec, int position)
{
	pid_t	pid;
	int heredoc_pipe[2];
	char *doc;
	int heredoc_flag;

	heredoc_flag = 0;
	doc = NULL;
	if (node->redir && node->redir->type == HEREDOC)
	{
		printf("heredoc in exec_child\n");
		heredoc_flag = 1;
		doc = handle_heredoc(node);
        if (pipe(heredoc_pipe) == -1)
        {
            perror("pipe");
            free(doc);
            return -1;
        }
        write(heredoc_pipe[1], doc, ft_strlen(doc));
        close(heredoc_pipe[1]);
        free(doc);
	}
	//printf("exec child: before fork\n");
	pid = fork();
	run_signals(2, node->msh);
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		//printf("we we 1\n");
		if (node->redir)
		{
			if (set_redirection(node) == -1)
			{
				clear_history();
                close_pipes(pipes, exec->node_amount - 1);
                free_pipes(pipes, exec->node_amount - 1);
                free_msh(node->msh);
                free_node_list(node);
                free_exec(exec);
				exit(-1);
			}
		}
		//printf("we we 2\n");

		if (pipes)
			set_pipe_ends(pipes, position, exec->node_amount - 1);
		if (heredoc_flag == 1)
		{	printf("heredoc pipe\n");
			close(heredoc_pipe[1]);
			dup2(heredoc_pipe[0], STDIN_FILENO);
			close(heredoc_pipe[0]);
		}
		//printf("we we 3\n");
			// if (node->redir->type == HEREDOC)
		// {
		// 	close(pipes[position-1][1]);
		// 	close(pipes[position-1][0]);
		// }
		if (node->cmd != NULL)
			exec_cmd(node, pipes, exec);
		//printf("exec child:free after node->cmd == NULL\n");
		clear_history();
		close_pipes(pipes, exec->node_amount - 1);
		free_pipes(pipes, exec->node_amount - 1);
		free_msh(node->msh);
		free_redir_list(node->redir);
		free_node_list(node);
		free_exec(exec);
		exit(0);
	}
	return (pid);
}

int	single_node(t_node_list *head, int **pipes, t_exec *exec)
{
	if(exec->node_amount == 1 && find_builtin(head) == 0)
	{
		//ft_dprintf("enter if builtin node single\n");
		if (head->redir)
		{
			if(head->redir->type == HEREDOC)
			{	printf("heredoc in single node\n");
				char *doc;
				doc = handle_heredoc(head);
				write(1, doc, ft_strlen(doc));
				free(doc);
			}
			if (set_redirection(head) == -1)
			{
				free_pipes(pipes, exec->node_amount - 1);
				reset_in_out(exec->stds_cpy);
				return (-1);
			}
		}
		if (head->cmd && find_builtin(head) == 0)
		{
			if ((exec_builtin(head, exec)) == 0)
			{
				//ft_dprintf("enter exec_builtin node single\n");
				free_pipes(pipes, exec->node_amount - 1);
				reset_in_out(exec->stds_cpy);
			}
		}
		else if (head->cmd && find_builtin(head) == 1)
			return (2);
		return (0);
	}
	return (1);
}

int	set_and_init(t_node_list *node_list, t_exec **exec, int ***pipes)
{
	*exec = malloc(sizeof(t_exec));
	if (!*exec)
		return (node_list->msh->exit_code = 1);
	(*exec)->msh = node_list->msh;
	(*exec)->exit_code = 0;
	(*exec)->last_pid = 0;
	(*exec)->node_amount = count_nodes(node_list);
	(*exec)->stds_cpy[0] = dup(STDIN_FILENO);
	(*exec)->stds_cpy[1] = dup(STDOUT_FILENO);
	if ((*exec)->stds_cpy[0] == -1 || (*exec)->stds_cpy[1] == -1)
		return (node_list->msh->exit_code = 1);
	if ((*exec)->node_amount > 1)
	{
		*pipes = pipe_init((*exec)->node_amount - 1);
		if (*pipes == NULL)
			return (node_list->msh->exit_code = 1);
	}
	else
		*pipes = NULL;
	return (0);
}

void	exec_nodes(t_node_list *node_list)
{
	t_node_list	*head;
	int			**pipes;
	int			i;
	t_exec		*exec;
	t_node_list *temp;

	exec = NULL;
	if (set_and_init(node_list, &exec, &pipes) == 1)
		return ;
	i = 0;
	//exec_heredoc(node_list);
	head = node_list;
	while (head)
	{
		exec->exit_code = single_node(head, pipes, exec);
		if (exec->exit_code == -1 || exec->exit_code == 0)
			break ;
		exec->last_pid = exec_child(head, pipes, exec, i);
		if (exec->last_pid == -1)
			break ;
		temp = head;
		head = head->next;
		free_cmd_struct(temp->cmd);
		free_redir_list(temp->redir);
		free(temp);
		i++;
	}
	close_execution(exec, pipes);
	free_exec(exec);
}
