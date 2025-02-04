// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execution.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: stdi-pum <stdi-pum@student.42berlin.de>    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/24 17:18:34 by jslusark          #+#    #+#             */
// /*   Updated: 2025/01/27 16:08:37 by stdi-pum         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../../include/minishell.h"

void reset_in_out(int std_in, int std_out)
{
    if (dup2(std_in, STDIN_FILENO) == -1)
        return;
    close(std_in);
    if (dup2(std_out, STDOUT_FILENO) == -1)
        return;
    close(std_out);
}

int exec_child(t_node_list *node, int **pipes, int node_amount, int position)
{
	pid_t pid;
	int exit_code;

	exit_code = 0;
    ft_dprintf("exec_child\n");
    pid  = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        if (pipes)
			set_pipe_ends(pipes, position, node_amount - 1);
        if(node->redir)
        {
            if(set_redirection (node) == -1)
                _exit(-1);
        }
        if (node->cmd != NULL)
		{
			if (exec_builtin(node) == 0)
				_exit(0);
			if ((exit_code = exec_external(node->cmd, node->msh)) != 0)
			{
				node->msh->exit_code = exit_code;
				_exit(exit_code);
			}
		}
		_exit(0);
    }
	return (0);
}

int single_node(t_node_list *head, int **pipes, int node_amount, int std_in, int std_out)
{
    if (node_amount == 1 && (find_builtin(head) == 0))
	{
        if(head->redir)
        {
            if(set_redirection (head) == -1)
			{
				free_pipes(pipes, node_amount - 1); // Free allocated memory for pipes
				reset_in_out(std_in, std_out);
                return(-1);
			}
        }
        if ((exec_builtin(head)) == 0)
        {
		    free_pipes(pipes, node_amount - 1); // Free allocated memory for pipes
	        reset_in_out(std_in, std_out);
            return (0);
        }
	}
    return (1);
}

int set_and_init(t_node_list *node_list, int *node_amount, int *std_in, int *std_out, int ***pipes)
{
    *node_amount = count_nodes(node_list);
    *std_in = dup(STDIN_FILENO);
    *std_out = dup(STDOUT_FILENO);
    if (*std_in == -1 || *std_out == -1)
        return (1);
    if (*node_amount > 1)
    {
        *pipes = pipe_init(*node_amount - 1); // node_amount - 1 pipes needed for node_amount commands
        if (*pipes == NULL)
            return (1);
    }
	else
		*pipes = NULL;
    return (0);
}

void	exec_nodes (t_node_list *node_list)
{
    int node_amount;
    t_node_list *head;
    int **pipes;
    int i;
    int std_in;
    int std_out;
	int exit_code;

    ft_dprintf("exec_nodes\n");
    if (set_and_init(node_list, &node_amount, &std_in, &std_out, &pipes) == 1)
    {
        ft_dprintf("Error: set_and_init function");
        node_list->msh->exit_code = 1;
        return ;
    }
    i = 0;
    head = node_list;
    while (head)
    {
        exit_code = single_node(head, pipes, node_amount, std_in, std_out);
		if(exit_code == -1 || exit_code == 0)
			return ;
		if ((exit_code = exec_child(head, pipes, node_amount, i)) != 0)
			break ;
        head = head->next;
        i++;
    }
    reset_in_out(std_in, std_out);
	if((exit_code = close_wait_free(pipes, node_amount)) == 255)
		node_list->msh->exit_code = 1;
	else if(exit_code == 13)
		node_list->msh->exit_code = 0;
	else
		node_list->msh->exit_code = exit_code;
	return ;
}
/*  REDIR error in single node = -1
	BUILTIN success in single node = 0
	CHILD error = 1*/