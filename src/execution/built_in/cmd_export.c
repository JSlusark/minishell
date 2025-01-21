/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:20:00 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/21 13:16:31 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void    handle_export(char **av, t_node_list *node)
{
    if (av == NULL)
    {
        printf("implement export listing all variables \n");
        node->msh->exit_code = 0;
		return ;
    }
    if (!ft_strchr(av[0], '='))
    {
        printf("implement add to matrix as empty variable\n");
        node->msh->exit_code = 0;
    }
    ms_set_env(node->msh, av[0]);
    
}