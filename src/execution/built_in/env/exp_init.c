/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:08 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 15:33:11 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void    ms_exp_init(t_msh **msh, char **envp)
{
    int i;

    i = 0;
    if (!envp)
    {
        fprintf(stderr, "Error: env is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (msh == NULL)
    {
        fprintf(stderr, "msh malloc failed\n");
        exit(EXIT_FAILURE);
    }
    while (envp[i])
        i++;
    (*msh)->env_exp = (char **)malloc(sizeof(char *) * (i + 1));
    if (!(*msh)->env_exp)
    {
        perror ("malloc failed\n");
        exit (EXIT_FAILURE);
    }
    i = 0;
    while (envp[i])
    {
        (*msh)->env_exp[i] = ft_strdup (envp[i]);
        i++;
    }
    (*msh)->env_exp[i] = NULL;
    check_shlvl(&(*msh)->env_exp);
}
