/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:18:34 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 18:16:22 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// I ONLY COMMENTED THE EXECUTING MESSAGE TO TRY THE TESTER


/*
	BUILT-INS
	They are commands that operate in the shell and that are used in our nodes.
	They are stored as binaries inside our computer, typically the usr/bin/ path (on linux).
	The path to a built it would typically be like this:

	/usr/bin/builtin_name

	We have to recreate the folling builtins that we will then execute in our shell:
	echo
	cd
	pwd
	export
	unset
	exit

	We should also execute all the other builtins that we do not need to recreate (like cat or grep for example)
	and we have to grab them from /usr/bin/ path in our linux pc

	THE CODE BELOW IS A ROUGH IDEA ON HOW WE CAN GET STARTED WITH EXECUTION.

Exit Codes and meaning (we should remember to assign them after parsing and executing)
	0 	- Success: Command executed successfully.
	1 	- General error: Command failed for a generic reason.
	2 	- Incorrect usage: Invalid arguments or syntax in the command <----- will be added as parsing error
	126	- Cannot execute: File exists but is not executable.
	127	- Command not found: Command is missing in the system's PATH.   -
	130	- Script interrupted (SIGINT): Process terminated via Ctrl+C.
 */

void 	exec_command(t_node_list	*node_list)
{
	if (strcmp(node_list->cmd->cmd, "echo") == 0)
		exec_echo(node_list);
	else if (strcmp(node_list->cmd->cmd, "pwd") == 0)
		exec_pwd(node_list); // <------- commentato per evitare comp error dato che non e' stato aggiunto nel tuo push
	else if (strcmp(node_list->cmd->cmd, "cd") == 0)
		exec_cd(node_list);
	else if (strcmp(node_list->cmd->cmd, "export") == 0)
		exec_export(node_list->cmd->args, node_list);
	else if (strcmp(node_list->cmd->cmd, "unset") == 0)
		exec_unset(node_list->cmd->args, node_list);
	else if (strcmp(node_list->cmd->cmd, "env") == 0)
		exec_env(node_list);
	else if (strcmp(node_list->cmd->cmd, "exit") == 0)
		exec_exit(node_list);//exec_exit(node_list, node_list->args->value); TO BE IMPLEMENTED ONCE THE CMD STRUCT IS UPDATED
	else
	{
		printf(COLOR_GREEN"Minishell> "COLOR_RESET); // <-- era stato rimosso prima, non so se era voluto
		printf("%s: command not found\n", node_list->cmd->cmd); // JESS: aggiunto per replicare lo stesso mesaggio di bash
		node_list->msh->exit_code = 127;
	}
}

int count_nodes(t_node_list	*node_list)
{
	int n = 0;
		while (node_list)
	{
		n++;
		node_list = node_list->next;
	}
	return(n);
}

void	exec_nodes(t_node_list	*node_list)
{
	int node_amount = count_nodes(node_list); // <---- secondo me possiamo togliere questa funzione
	if (node_amount > 1) 					 // e sostituire qui con "if (node->next)"
	{
		// printf(COLOR_YELLOW"\nEXECUTING PIPES WITH %d NODES...\n"COLOR_RESET, node_amount);
	}
	else
	{
		if(node_list->cmd)
				exec_command(node_list);
		else
		{
			// printf("Minishell: node does not have a command, check for redirs\n");
		}
	}
}
