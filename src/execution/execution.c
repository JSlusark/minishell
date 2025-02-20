/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 23:54:49 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/20 18:02:48 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_execution(t_exec *exec, int **pipes)
{
	// printf( COLOR_RED"exec->exit_code EXIT BEFORE RESET 1 ->  %d \n" COLOR_RESET, exec->exit_code);
	// printf( COLOR_GREEN"exec->msh->exit_code EXIT BEFORE RESET 1 ->  %d \n"COLOR_RESET, exec->msh->exit_code);
	reset_in_out(exec->stds_cpy);
	// printf( COLOR_RED"exec->exit_code EXIT AFTER RESET 2 -> %d \n"COLOR_RESET, exec->exit_code);
	// printf( COLOR_GREEN"exec->msh->exit_code EXIT AFTER RESET 2 -> %d \n"COLOR_RESET, exec->msh->exit_code);
	exec->exit_code = close_wait_free(pipes, exec->node_amount, exec->last_pid);
	// printf( COLOR_RED"exec->exit_code EXIT AFTER CLOSE_WAIT FREE 3 -> %d \n"COLOR_RESET, exec->exit_code);
	// printf( COLOR_GREEN"exec->msh->exit_code EXIT AFTER CLOSE_WAIT FREE 3 ->%d \n"COLOR_RESET, exec->msh->exit_code);
	if (exec->exit_code == 255)
		exec->msh->exit_code = 1;
	else if (exec->exit_code == 13)
		exec->msh->exit_code = 0;
	else if (exec->exit_code == 1 || exec->msh->exit_code == 1 || exec->msh->exit_code == -1)
		exec->msh->exit_code = 1;
	else
		exec->msh->exit_code = exec->exit_code;
	// printf( COLOR_RED"exec->exit_code  -> %d \n"COLOR_RESET, exec->exit_code);
	// printf( COLOR_GREEN"exec->msh->exit_code -> %d \n"COLOR_RESET, exec->msh->exit_code);
}

int	exec_child(t_node_list *node, int **pipes, t_exec *exec, int position)
{
	pid_t	pid;
	int		heredoc_pipe[2];

	heredoc_pipe[0] = -1;
	if(node->redir)
		handle_heredoc(node, heredoc_pipe, exec);
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
		if (pipes)
			set_pipe_ends(pipes, position, exec->node_amount - 1);
		if (node->redir)
		{
			if (set_redirection(node) == -1)
			{
				exec->msh->exit_code = 1; // AGGIUNTO PER CONTROLLO
				clear_history();
                close_pipes(pipes, exec->node_amount - 1);
                free_pipes(pipes, exec->node_amount - 1);
                free_msh(node->msh);
                free_node_list(node);
                free_exec(exec);
				exit(-1);
			}
		}
		if (heredoc_pipe[0] != -1)
		{
			close(heredoc_pipe[1]);
			dup2(heredoc_pipe[0], STDIN_FILENO);
			close(heredoc_pipe[0]);
		}
		if (node->cmd != NULL)
			exec_cmd(node, pipes, exec);
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
	int heredoc_pipe[2];

	heredoc_pipe[0] = -1;
	if(exec->node_amount == 1 && find_builtin(head) == 0)
	{
		// ft_dprintf("enter if builtin node single\n");
		if (head->redir)
		{
			handle_heredoc(head, heredoc_pipe, exec);
			if (set_redirection(head) == -1)
			{
				// printf("Single node 1 - exit %d\n", head->msh->exit_code);
				if (heredoc_pipe[0] != -1)
					close(heredoc_pipe[0]);
				free_pipes(pipes, exec->node_amount - 1);
				reset_in_out(exec->stds_cpy);
				return (-1);
			}
		}
		if ((exec_builtin(head, exec, pipes)) == 0) // QUA e' il builtin con le pipes?
		{
			// printf("Single node 2 - exit %d\n", head->msh->exit_code);
			if (heredoc_pipe[0] != -1)
				close(heredoc_pipe[0]);
			// printf("Single node 3 - exit %d\n", head->msh->exit_code);
			free_pipes(pipes, exec->node_amount - 1);
			reset_in_out(exec->stds_cpy);
			// printf("Single node 4 - exit %d\n", head->msh->exit_code);
			// printf("flag %d\n", *flag);
			// DEVE RITORNARE QUALCOSA E FERMARSI NO?
		}
		else if (head->cmd && find_builtin(head) == 1)
		{
			// printf("Single node 5 - exit %d\n", head->msh->exit_code);
			return (2);
		}

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

void	exec_nodes(t_node_list *node_list, int *msh_exit)
{
	(void)msh_exit;
	t_node_list	*head;
	int			**pipes;
	int			i;
	t_exec		*exec;
	t_node_list *temp;
	int exit;
	int redir_exit_flag;
	int stored_exit;
	redir_exit_flag = 0;
	stored_exit = 0;
	exec = NULL;
	if (set_and_init(node_list, &exec, &pipes) == 1)
		return ;
	i = 0;
	head = node_list;
	exit = 0;
	while (head)
	{
		temp = head;
		exit = single_node(head, pipes, exec); // AGGIUNTO PER CONTROLLO
		// printf("BUILTIN EXEC->MSH->EXIT_CODE %d \n", exec->msh->exit_code);
		if (exit == -1 || exit == 0) // AGGIUNTO PER CONTROLLO
		{
			free_cmd_struct(temp->cmd);
			free_redir_list(temp->redir);
			free(temp);
			// printf("BREAK FROM -1/ 0 | EXEC->MSH->EXIT_CODE %d \n", exec->msh->exit_code);
			break ;
		}
		exec->last_pid = exec_child(head, pipes, exec, i);
		if (exec->last_pid == -1)
		{
			free_cmd_struct(temp->cmd);
			free_redir_list(temp->redir);
			free(temp);
			// printf("BREAK FROM EXEC->LAST_PID - 1 | EXEC->MSH->EXIT_CODE %d \n", exec->msh->exit_code);
			break ;
		}
		head = head->next;
		free_cmd_struct(temp->cmd);
		free_redir_list(temp->redir);
		free(temp);
		i++;
	}
	// printf("redir in exit_flag %d \n", redir_exit_flag);
	// printf("exec->msh->exit_code BEFORE close_exec %d \n", exec->msh->exit_code);
	// printf("exec->exit_code BEFORE close_exec: %d\n", exec->exit_code);
	close_execution(exec, pipes);
	// printf("exec->msh->exit_code AFTER close_exec %d \n", exec->msh->exit_code);
	// printf("exec->exit_code AFTER close_exec: %d\n", exec->exit_code);
	// stored_exit = exec->msh->exit_code;
	// printf("Stored exit AFTER close execution %d \n",stored_exit);
	free_exec(exec);
	// printf("exec->msh->exit_code AFTER free_exec %d \n", exec->msh->exit_code);
	// printf("exec->exit_code AFTER free_exec %d\n", exec->exit_code);
	// *msh_exit = stored_exit;
}
