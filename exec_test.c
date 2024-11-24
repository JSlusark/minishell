/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:18:34 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/24 19:14:34 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
 */

void exec_command(t_node	*node)
{
	if(strcmp(node->cmd_data->cmd_value, "echo") == 0)
		printf(COLOR_GREEN"\nEXECUTING < ECHO > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd_data->cmd_value, "cd") == 0)
		printf(COLOR_GREEN"\nEXECUTING < CD > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd_data->cmd_value, "pwd") == 0)
		printf(COLOR_GREEN"\nEXECUTING < PWD > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd_data->cmd_value, "export") == 0)
		printf(COLOR_GREEN"\nEXECUTING < EXPORT > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd_data->cmd_value, "unset") == 0)
		printf(COLOR_GREEN"\nEXECUTING < UNSET > BUILT-IN...\n\n"COLOR_RESET);
	else if(strcmp(node->cmd_data->cmd_value, "exit") == 0)
		printf(COLOR_GREEN"\nEXECUTING < EXIT > BUILT-IN...\n\n"COLOR_RESET);
	else if(node->cmd_data->cmd_type == ENV_VAR) // there are cases like "$PATH echo hello" which made me consider this but there might be other ways.. will think about it in the futue
		printf(COLOR_GREEN"\nFound env_var as node command, still need to figure out how thinsg work here! Try <$PATH echo hello> on bash !\n"COLOR_RESET);
	else
		printf(COLOR_GREEN"\nSEARCHING FOR /usr/bin/%s binary data AND EXECUTING..\n"COLOR_RESET, node->cmd_data->cmd_value);
}

int count_nodes(t_node	*node_list)
{
	int n = 0;
		while (node_list) // Iterate through the n list
	{
		n++;
		node_list = node_list->next; // Move to the next n
	}
	return(n);
}
void	exec_node(t_node	*node_list)
{
	int node_amount = count_nodes(node_list);
	if (node_amount > 1)
	{
		printf(COLOR_GREEN"\nEXECUTING PIPES WITH %d NODES...\n"COLOR_RESET, node_amount);
		printf("	- Let's focus on built-ns with single nodes first so that then we can use that same logic when we fork the execution of each node with pipes perhaps?\n");
	}
	else
		exec_command(node_list);
}