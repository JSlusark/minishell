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

// // I ONLY COMMENTED THE EXECUTING MESSAGE TO TRY THE TESTER


// /*
// 	BUILT-INS
// 	They are commands that operate in the shell and that are used in our nodes.
// 	They are stored as binaries inside our computer, typically the usr/bin/ path (on linux).
// 	The path to a built it would typically be like this:

// 	/usr/bin/builtin_name

// 	We have to recreate the folling builtins that we will then execute in our shell:
// 	echo
// 	cd
// 	pwd
// 	export
// 	unset
// 	exit

// 	We should also execute all the other builtins that we do not need to recreate (like cat or grep for example)
// 	and we have to grab them from /usr/bin/ path in our linux pc

// 	THE CODE BELOW IS A ROUGH IDEA ON HOW WE CAN GET STARTED WITH EXECUTION.

// Exit Codes and meaning (we should remember to assign them after parsing and executing)
// 	0 	- Success: Command executed successfully.
// 	1 	- General error: Command failed for a generic reason.
// 	2 	- Incorrect usage: Invalid arguments or syntax in the command <----- will be added as parsing error
// 	126	- Cannot execute: File exists but is not executable.
// 	127	- Command not found: Command is missing in the system's PATH.   -
// 	130	- Script interrupted (SIGINT): Process terminated via Ctrl+C.
//  */

void reset_in_out(int std_in, int std_out)
{
    dup2(STDIN_FILENO, std_in);
    dup2(STDOUT_FILENO, std_out);
}

void exec_child(t_node_list *node, int **pipes, int node_amount, int position)
{
	pid_t pid;

    ft_dprintf("exec_child\n");
    pid  = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        if(node->redir)
            set_redirection(node);

		if (pipes) 
			set_pipe_ends(pipes, position, node_amount - 1);
		if (node->cmd != NULL) 
		{
			if (exec_builtin(node) == 0)
				_exit(EXIT_SUCCESS);
			if (exec_external(node->cmd, node->msh->ms_env) == 1) 
			{
				perror("exec_external");
				_exit(EXIT_FAILURE);
			}
		}
    	_exit(EXIT_SUCCESS);
    }
}

void	exec_nodes (t_node_list *node_list)
{
    int node_amount;
    t_node_list *head;
    int **pipes;
    int i;
    int std_in;
    int std_out;

    ft_dprintf("exec_nodes\n");
    head = node_list;
	if(check_cmds(node_list) == 1)
		return ;
    node_amount = count_nodes(node_list);
    std_in = dup(STDIN_FILENO);
    std_out = dup(STDOUT_FILENO);
    if (std_in == -1 || std_out == -1)
        return;
    if (node_amount > 1)
    {
        pipes = pipe_init(node_amount - 1); // node_amount - 1 pipes needed for node_amount commands
        if (pipes == NULL)
            return;
    }
	else 
		pipes = NULL;
    i = 0;
    while (head)
    {
        if(head->redir)
            set_redirection(head);
		if(node_amount == 1 && (exec_builtin(head)) == 0)
		{
			free_pipes(pipes, node_amount - 1); // Free allocated memory for pipes
			break ;
		}
		exec_child(head, pipes, node_amount, i);
        head = head->next;
        i++;
    }
    if (dup2(std_in, STDIN_FILENO) == -1)
        return;
    close(std_in);

    if (dup2(std_out, STDOUT_FILENO) == -1)
        return;
    close(std_out);
	close_wait_free(pipes, node_amount);

    // reset_in_out(std_in, std_out);
}