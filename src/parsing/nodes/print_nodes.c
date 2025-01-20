/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/20 13:16:40 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


/* ___________________ TERMINAL PRINT FUNCTION ____________________*/

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
	// printf("function calling is: %s\n", __func__);
	int n = 0;

	printf(COLOR_GREEN"\nNODE LIST TO ITERATE AND EXECUTE...\n"COLOR_RESET); // Print the node_i value
	t_node_list *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{
		n++;
		printf(COLOR_YELLOW"	- NODE %d\n"COLOR_RESET, n); // Print the node_i value
		printf(COLOR_BLUE"		- int node_i:"COLOR_RESET); // Print the node_i value
		printf(" %d\n", curr->node_i); // Print the node_i value
		if (curr->cmd)
		{
			printf(COLOR_BLUE"		- t_cmd cmd:\n"COLOR_RESET); // Print the node_i value
			printf("			- char *cmd: %s\n", curr->cmd->cmd); // Print the node_i value
			print_args(curr->cmd->args);

			// printf("			- int type: %s\n", return_token_enum(curr->cmd->type)); // Print the node_i value
		}
		if (!curr->cmd)
		{
			printf(COLOR_BLUE"		- t_cmd cmd: "COLOR_RESET); // Print the node_i value
			printf("null\n"); // Print the node_i value
		}
		if (curr->cmd->option_n)
		{
			printf(COLOR_BLUE"		- bool option -n:"COLOR_RESET); // Print the node_i value
			printf(" true\n"); // Print the node_i value
		}
		if (!curr->cmd->option_n)
		{
			printf(COLOR_BLUE"		- bool option -n:"COLOR_RESET); // Print the node_i value
			printf(" false\n"); // Print the node_i value
		}
		// print_args(curr->args);
		print_redir(curr->redir);
		curr = curr->next; // Move to the next node
	}
	printf("\n	Total number of pipes: %d\n", n - 1); // Print the node_i value
	printf("	Total number of nodes: %d\n", n); // Print the node_i value
}

/* ________________________________________________________________*/




/* ___________________ OUT FILE PRINT FUNCTION ____________________*/
/*
	copiato e incollato la stessa logica di sopra ma questa va in seg fault (con "echo arg1 arg2 arg3") o
	non stampa proprio gli argomenti (con "echo ciao" esce che args e' NULL)
 */

void print_redir_in_outfile(t_redir *head)
{
	if (!head)
	{
		ft_dprintf("		- t_redir redir:");
		ft_dprintf(" null\n");
		return;
	}
	t_redir *current = head;
	ft_dprintf("		- t_redir redir:\n");
	while (current)
	{
		ft_dprintf("			- REDIR N %d:\n", current->redir_i + 1);
		ft_dprintf("			  - int type: %s\n", return_token_enum(current->type));

		ft_dprintf("			  - char *target: %s (%s)\n", current->target_name, return_token_enum(current->type));
		ft_dprintf("			  - int target_type: %s\n", return_target_enum(current->type));
		current = current->next; // Move to the next argument in the list
	}
}

void print_args_in_outfile(char **args)
{
if (!args || !args[0]) // Check if the args array is NULL or empty
	{
		ft_dprintf("			- char **args:");
		ft_dprintf(" null\n");
		return;
	}
	ft_dprintf("			- char **args:\n");
	for (int i = 0; args[i]; i++) // Loop through the args array until NULL
	{
		ft_dprintf("			  *arg[%d]: %s\n",i , args[i]);
	}
}

void print_nodes_in_outfile(t_node_list *head)
{
	// ft_dprintf("function calling is: %s\n", __func__);
	int n = 0;

	ft_dprintf("\nNODE LIST TO ITERATE AND EXECUTE...\n"); // Print the node_i value
	t_node_list *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{
		n++;
		ft_dprintf("	- NODE %d\n", n); // Print the node_i value
		ft_dprintf("		- int node_i:"); // Print the node_i value
		ft_dprintf(" %d\n", curr->node_i); // Print the node_i value
		if (curr->cmd)
		{
			ft_dprintf("		- t_cmd cmd:\n"); // Print the node_i value
			ft_dprintf("			- char *cmd: %s\n", curr->cmd->cmd); // Print the node_i value
			print_args_in_outfile(curr->cmd->args);

			// ft_dprintf("			- int type: %s\n", return_token_enum(curr->cmd->type)); // Print the node_i value
		}
		if (!curr->cmd)
		{
			ft_dprintf("		- t_cmd cmd: "); // Print the node_i value
			ft_dprintf("null\n"); // Print the node_i value
		}
		if (curr->cmd->option_n)
		{
			ft_dprintf("		- bool option -n:"); // Print the node_i value
			ft_dprintf(" true\n"); // Print the node_i value
		}
		if (!curr->cmd->option_n)
		{
			ft_dprintf("		- bool option -n:"); // Print the node_i value
			ft_dprintf(" false\n"); // Print the node_i value
		}
		// print_args(curr->args);
		print_redir_in_outfile(curr->redir);
		curr = curr->next; // Move to the next node
	}
	ft_dprintf("\n	Total number of pipes: %d\n", n - 1); // Print the node_i value
	ft_dprintf("	Total number of nodes: %d\n", n); // Print the node_i value
}




