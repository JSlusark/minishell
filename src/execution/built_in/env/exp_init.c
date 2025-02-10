/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:08:08 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 14:35:38 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int exp_compare(char **env, char **av, int i)
{
    char    **split;

    while (env[i])
    {
        split = ft_split (env[i], '=');
        if (ft_strcmp(split[0], av[0]) == 0)
        {
            ft_free_tab(split);
            break ;
        }
        ft_free_tab (split);
        i++;
    }
    return (i);
}

void    ms_set_exp(t_msh *msh, char *value)
{
    int     i;
    char    **av;

    i = 0;
    av = ft_split (value, '='); //if split does not find '=', av [0] == nome della variabile.
    i = exp_compare(msh->env_exp, av, i);
    if (msh->env_exp[i] == NULL)
        msh->env_exp = ms_matrix_add_line(msh->env_exp, value);
    else
    {
        free (msh->env_exp[i]);
        msh->env_exp[i] = ft_strdup (value);
    }
    ft_free_tab (av);
}

// void    ft_free_tab(char **tab)
// {
//     int i;

//     i = 0;
//     while (tab[i])
//     {
//         free (tab[i]);
//         i++;
//     }
//     free (tab);
// }

char    *ms_get_varexp(char **env, char *av)
{
    int     i;
    char    **split;
    char    *var_env;

    i = 0;
    var_env = NULL;
    while (env[i] && !var_env)
    {
        split = ft_split (env[i], '=');
        if (ft_strcmp(split[0], av) == 0)
            var_env = ft_strdup(split[1]);
        else
            i++;
        ft_free_tab (split);
    }
    if (env[i] == NULL)
        return (NULL);
    return (var_env);
}

// char	**ms_matrix_add_line(char **matrix, char *new_line)
// {
// 	int		i;
// 	char	**new_matrix;

// 	i = 0;
// 	while (matrix[i])
// 		i++;
// 	new_matrix = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		new_matrix[i] = ft_strdup(matrix[i]);
// 		i++;
// 	}
// 	new_matrix[i] = ft_strdup(new_line);
// 	i++;
// 	new_matrix[i] = NULL;
// 	ft_free_tab(matrix);
// 	return (new_matrix);
// }

char    *ms_get_exp(t_msh *msh, char *av)
{
    int     i;
    char    **split;

    i = 0;
    while (msh->env_exp[i])
    {
        split = ft_split (msh->env_exp[i], '=');
        if (ft_strcmp(split[0], av) == 0)
        {
            ft_free_tab (split);
            break ;
        }
        else
            i++;
        ft_free_tab (split);
    }
    if (msh->env_exp[i] == NULL)
        return (NULL);
    return (msh->env_exp[i]);
}

void    check_shlvl_exp(t_msh *msh)
{
    char    *var;
    char    *value;
    int     shlvl;
    char    *new_var;

    var = ms_get_exp (msh, "SHLVL");
    if (!var)
    {
        msh->env_exp = ms_matrix_add_line(msh->env_exp, "SHLVL=1");
        return ;
    }
    value = ms_get_varexp (msh->env_exp, "SHLVL");
    if (!value || ft_isdigit(value[0]) == 0)
    {
        printf("Warning: invalid SHLVL value. Resetting to 1\n");
        free (value);
        msh->env_exp = ms_matrix_add_line (msh->env_exp, "SHLVL=1");
        return ;
    }
    shlvl = ft_atoi (value);
    free (value);
    if (shlvl < 0)
        shlvl = 1;
    else
        shlvl++;
    value = ft_itoa (shlvl);
    new_var = ft_strjoin ("SHLVL=", value);
    free (value);
    ms_set_exp (msh, new_var);
    free (new_var);
}

void    ms_exp_init(t_msh **msh, char **envp)
{
    int i;

    i = 0;
    if (!envp)
    {
        fprintf(stderr, "Error: env is NULL\n");
        exit(EXIT_FAILURE);
    }
    // *msh = malloc(sizeof(t_msh));
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
    check_shlvl_exp((*msh));
    // (*msh)->exit_code = 0;
    // (*msh)->prev_exit = 0;
}
