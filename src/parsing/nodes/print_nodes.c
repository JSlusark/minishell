/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:06:38 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 12:27:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*return_token_enum(int token_type)
{
	if (token_type == REDIR_IN)
		return ("REDIR_IN (<)");
	else if (token_type == REDIR_OUT)
		return ("REDIR_OUT (>)");
	else if (token_type == APPEND)
		return ("APPEND (>>)");
	else if (token_type == HEREDOC)
		return ("HEREDOC (<<)");
	else if (token_type == PIPE)
		return ("PIPE");
	else if (token_type == ARG)
		return ("ARG");
	else if (token_type == INVALID)
		return ("INVALID");
	else
		return ("UNRECOGNISED_ENUM");
}

char	*return_target_enum(int redir_type)
{
	if (redir_type == 7)
		return ("DELIMITER");
	return ("FILE");
}

void	print_redir(t_redir *head)
{
	t_redir *current;

	if (!head)
	{
		printf(COLOR_BLUE"		- t_redir redir:"COLOR_RESET);
		printf(" null\n");
		return ;
	}
	current = head;
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
	if (!args || !args[0])
	{
		printf("			- char **args:");
		printf(" null\n");
		return ;
	}
	printf("			- char **args:\n");
	for (int i = 0; args[i]; i++)
	{
		printf("			  *arg[%d]: %s\n",i , args[i]);
	}
}

void	print_nodes(t_node_list *head)
{
	t_node_list	*curr;
	int			n;

	n = 0;
	curr = head;
	printf(COLOR_GREEN"\nNODE LIST TO ITERATE AND EXECUTE...\n"COLOR_RESET);
	while (curr != NULL)
	{
		n++;
		printf(COLOR_YELLOW"	- NODE %d\n"COLOR_RESET, n);
		printf(COLOR_BLUE"		- int node_i:"COLOR_RESET);
		printf(" %d\n", curr->node_i);
		if (curr->msh)
		{
			printf(COLOR_BLUE"		- node->msh: \n"COLOR_RESET);
			printf("			- exit_code: ");
			printf("%d\n", curr->msh->exit_code);
			printf("			- prev_exit: ");
			printf("%d\n", curr->msh->prev_exit);
		}
		if (!curr->cmd)
		{
			printf(COLOR_BLUE"		- t_cmd cmd: "COLOR_RESET);
			printf("null\n");
			printf("			- char **args:");
			printf(" null\n");
			printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET);
			printf(" null\n");
		}
		else
		{
			printf(COLOR_BLUE"		- t_cmd cmd:\n"COLOR_RESET);
			printf("			- char *cmd: %s\n", curr->cmd->cmd);
			print_args(curr->cmd->args);
			if (curr->cmd->option_n)
			{
				printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET);
				printf(" true\n");
			}
			if (!curr->cmd->option_n)
			{
				printf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET);
				printf(" false\n");
			}
		}
		print_redir(curr->redir);
		curr = curr->next;
	}
	printf("\n	Total number of pipes: %d\n", n - 1);
	printf("	Total number of nodes: %d\n", n);
}
