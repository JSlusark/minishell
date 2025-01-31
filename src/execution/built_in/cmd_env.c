/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:26:33 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/26 18:26:34 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int handle_env(t_node_list *node)
{
	int i;

	i = 0;
	while (node->msh->ms_env[i])
	{
		printf("%s\n", node->msh->ms_env[i++]);
	}
	return (0);
}
