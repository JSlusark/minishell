/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes_outfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:49 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 12:24:20 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*return_token_enum_out(int token_type)
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

char	*return_target_enum_out(int redir_type)
{
	if (redir_type == 7)
		return ("DELIMITER");
	return ("FILE");
}

/* ___________________ OUT FILE PRINT FUNCTION ____________________*/
void	print_redir_in_outfile(t_redir *head)
{
	t_redir	*current;

	if (!head)
	{
		ft_dprintf("		- t_redir redir:");
		ft_dprintf(" null\n");
		return ;
	}
	current = head;
	ft_dprintf("		- t_redir redir:\n");
	while (current)
	{
		ft_dprintf("			- REDIR N %d:\n", current->redir_i + 1);
		ft_dprintf("			  - int type: %s\n", return_token_enum_out(current->type));
		ft_dprintf("			  - char *target: %s (%s)\n", current->target_name, return_token_enum_out(current->type));
		ft_dprintf("			  - int target_type: %s\n", return_target_enum_out(current->type));
		current = current->next;
	}
}

void	print_args_in_outfile(char **args)
{
	if (!args || !args[0])
	{
		ft_dprintf("			- char **args:");
		ft_dprintf(" null\n");
		return ;
	}
	ft_dprintf("			- char **args:\n");
	for (int i = 0; args[i]; i++) // Loop through the args array until NULL
	{
		ft_dprintf("			  *arg[%d]: %s\n",i , args[i]);
	}
}

void	print_nodes_in_outfile(t_node_list *head)
{
	int	n;

	n = 0;
	ft_dprintf("\nNODE LIST TO ITERATE AND EXECUTE...\n"); // Print the node_i value
	t_node_list *curr = head; // Start with the head of the node list
	while (curr != NULL)
	{
		n++;
		ft_dprintf("	- NODE %d\n", n); // Print the node_i value
		ft_dprintf("		- int node_i:"); // Print the node_i value
		ft_dprintf(" %d\n", curr->node_i); // Print the node_i value
		if (!curr->cmd)
		{
			ft_dprintf(COLOR_BLUE"		- t_cmd cmd: "COLOR_RESET); // Print the node_i value
			ft_dprintf("null\n"); // Print the node_i value
			ft_dprintf("			- char **args:");
			ft_dprintf(" null\n");
			ft_dprintf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
			ft_dprintf(" null\n");
		}
		else
		{
			ft_dprintf(COLOR_BLUE"		- t_cmd cmd:\n"COLOR_RESET); // Print the node_i value
			ft_dprintf("			- char *cmd: %s\n", curr->cmd->cmd); // Print the node_i value
			print_args_in_outfile(curr->cmd->args);
			if (curr->cmd->option_n)
			{
				ft_dprintf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
				ft_dprintf(" true\n"); // Print the node_i value
			}
			if (!curr->cmd->option_n)
			{
				ft_dprintf(COLOR_YELLOW"			- bool option -n:"COLOR_RESET); // Print the node_i value
				ft_dprintf(" false\n"); // Print the node_i value
			}
		}
		print_redir_in_outfile(curr->redir);
		curr = curr->next; // Move to the next node
	}
	ft_dprintf("\n	Total number of pipes: %d\n", n - 1); // Print the node_i value
	ft_dprintf("	Total number of nodes: %d\n", n); // Print the node_i value
}
