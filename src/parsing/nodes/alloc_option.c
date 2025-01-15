/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:02:05 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 11:59:28 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* bool is_nflag(char *value)
{
	int i;
	i = 0;
	if(value[i] == '-')
	{
		i++;
		if(value[i] != 'n')
			return(false);
	}
	// else
	// {
		while(value[i] == 'n')
			i++;
		if(value[i] == '\0') // -nnnnnnnnn is a valid -n flag for example
		{
			// printf("%s is true\n", value);
			return(true);
		}
		else // for example -nnnnnnnnm
		{
			// printf("%s is false\n", value);
			return(false);
		}
	// }
	return(true);
}

void	check_option(t_tokens **token, t_node_list *new_node)
{

	t_tokens *temp = *token; // Use a temporary pointer to avoid modifying *token

		printf("-n flag: %s\n", temp->value);
	while (temp->value[0] == '-' && is_nflag(temp->value))// while loop may cover edgecases when we have more than one consec -n
	{
		new_node->cmd->option_n = true; // Set the node's option flag
		if (temp->next)
			temp = temp->next;  // Move to the option toke
		else
			break;
	}
}
 */

// OLD KEEPING IT TO SEE WTF I DID WRONG WITH ABOVE
// void	check_option(t_tokens **token, t_node_list *new_node)
// {
// 	while ((*token)->type == OPTION)// while loop may cover edgecases when we have more than one consec -n
// 	{
// 		new_node->option_n = true; // Set the node's option flag
// 		if ((*token)->next && (*token)->next->type == OPTION)
// 			*token = (*token)->next;  // Move to the option toke
// 		else
// 			break;
// 	}
// }