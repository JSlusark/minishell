/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:18:34 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/13 18:26:18 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void exec_command(t_node_list	*node)
{
	if(strcmp(node->cmd->value, "cd") == 0)
		printf(COLOR_GREEN"\nEXECUTING < CD > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd->value, "echo") == 0)
	{
		t_args *current = node->args; // Assuming args is a linked list
		while (current != NULL) // Traverse until the end of the list
		{
			if (current->value != NULL) // Check if the current value is not NULL
				printf("%s", current->value); // Print the current argument value
			if (current->next != NULL)
				printf(" ");
			current = current->next; // Move to the next argument in the list
		}
		if(!node->option_n)
			printf("\n"); // print newline at end if -n_option is false
	}
	else if(strcmp(node->cmd->value, "exit") == 0)
	{
		printf(COLOR_GREEN"\nMinishell> "COLOR_RESET); // does not create leaks for now
		printf("Exiting minishell...\n");
		free_node_list(node);
		clear_history();
		exit(0);
	}
	else if(strcmp(node->cmd->value, "export") == 0)
		printf(COLOR_GREEN"\nEXECUTING < EXPORT > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd->value, "pwd") == 0)
		printf(COLOR_GREEN"\nEXECUTING < PWD > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd->value, "unset") == 0)
		printf(COLOR_GREEN"\nEXECUTING < UNSET > BUILT-IN...\n\n"COLOR_RESET);
	else if(node->cmd->type == ENV_VAR) // should be FILE OR PATHNAME and see if an executable is put as cmd
		printf(COLOR_GREEN"\nFound env_var as node command, still need to figure out how thinsg work here! Try <$PATH echo hello> on bash !\n"COLOR_RESET);
	else
		printf(COLOR_GREEN"\nSEARCHING FOR /usr/bin/%s binary data AND EXECUTING..\n"COLOR_RESET, node->cmd->value); // if this fails - error code 127 (command not found)
}

int count_nodes(t_node_list	*node_list)
{
	int n = 0;
		while (node_list) // Iterate through the n list
	{
		n++;
		node_list = node_list->next; // Move to the next n
	}
	return(n);
}
void	exec_nodes(t_node_list	*node_list)
{
	int node_amount = count_nodes(node_list);
	if (node_amount > 1)
	{
		printf(COLOR_GREEN"\nEXECUTING PIPES WITH %d NODES...\n"COLOR_RESET, node_amount);
		printf("	- Let's focus on built-ns with single nodes first so that then we can use that same logic when we fork the execution of each node with pipes perhaps?\n");
	}
	else
	{
		if(node_list->cmd)
			exec_command(node_list);
		else
			printf("Minishell: node does not have a command\n");
	}
}
