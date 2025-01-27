/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 17:13:50 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *return_token_enum(int token_type)
{
	if (token_type == REDIR_IN)
		return "REDIR_IN (<)"; // Input redirection ("<")
	else if (token_type == REDIR_OUT)
		return "REDIR_OUT (>)"; // Output redirection (">")
	else if (token_type == APPEND)
		return "APPEND (>>)"; // Append redirection (">>")
	else if (token_type == HEREDOC)
		return "HEREDOC (<<)"; // Here-document redirection ("<<")
	else if (token_type == PIPE)
		return "PIPE"; // Pipe operator ("|")
	else if (token_type == ARG)
		return "ARG"; // Any letter or number that is not quoted
	else if (token_type == INVALID)
		return "INVALID"; // Any letter or number that is not quoted
	else
		return "UNRECOGNISED_ENUM"; // For invalid enum values
}

char *return_target_enum(int redir_type)
{
	if(redir_type == 7) // enmum of heredoc
		return("DELIMITER");
	return("FILE");
}


void print_redir(t_redir *head)
{
	if (!head)
	{
		printf(COLOR_BLUE"		- t_redir redir:"COLOR_RESET);
		printf(" null\n");
		return;
	}
	t_redir *current = head;
	printf(COLOR_BLUE"		- t_redir redir:\n"COLOR_RESET);
	while (current)
	{
		printf(COLOR_CYAN"			- REDIR N %d:\n"COLOR_RESET, current->redir_i + 1);
		printf("			  - int type: %s\n", return_token_enum(current->type));

		printf("			  - char *target: %s (%s)\n", current->target_name, return_token_enum(current->type));
		printf("			  - int target_type: %s\n", return_target_enum(current->type));
		current = current->next; // Move to the next argument in the list
	}
}

void print_args(char **args)
{
if (!args || !args[0]) // Check if the args array is NULL or empty
	{
		printf("			- char **args:");
		printf(" null\n");
		return;
	}
	printf("			- char **args:\n");
	for (int i = 0; args[i]; i++) // Loop through the args array until NULL
	{
		printf("			  *arg[%d]: %s\n",i , args[i]);
	}
}

void print_nodes(t_node_list *head)
{
	int n = 0;

	printf(COLOR_GREEN"\nNODE LIST TO ITERATE AND EXECUTE...\n"COLOR_RESET); // Print the node_i value
	t_node_list *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{
		n++;
		printf(COLOR_YELLOW"	- NODE %d\n"COLOR_RESET, n); // Print the node_i value
		printf(COLOR_BLUE"		- int node_i:"COLOR_RESET); // Print the node_i value
		printf(" %d\n", curr->node_i); // Print the node_i value
		if (!curr->cmd)
		{
			printf(COLOR_BLUE"		- t_cmd cmd: "COLOR_RESET); // Print the node_i value
			printf("null\n"); // Print the node_i value
			printf("			- char **args:");
			printf(" null\n");
			printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
			printf(" null\n");
		}
		else
		{
			printf(COLOR_BLUE"		- t_cmd cmd:\n"COLOR_RESET); // Print the node_i value
			printf("			- char *cmd: %s\n", curr->cmd->cmd); // Print the node_i value
			print_args(curr->cmd->args);
			if (curr->cmd->option_n)
			{
				printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
				printf(" true\n"); // Print the node_i value
			}
			if (!curr->cmd->option_n)
			{
				printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
				printf(" false\n"); // Print the node_i value
			}
		}
		print_redir(curr->redir);
		curr = curr->next; // Move to the next node
	}
	printf("\n	Total number of pipes: %d\n", n - 1); // Print the node_i value
	printf("	Total number of nodes: %d\n", n); // Print the node_i value
}