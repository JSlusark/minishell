/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:04:03 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 15:31:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

// Compare environment variable names
int env_compare(char **env, char **av, int i)
{
    char    **split;

    while (env[i])
    {
        split = ft_split(env[i], '=');
        if (ft_strcmp(split[0], av[0]) == 0)
        {
            ft_free_tab(split);
            break;
        }
        ft_free_tab(split);
        i++;
    }
    return (i);
}

// Set environment variable
void ms_set_env(char ***env, char *value)
{
    int i;
    char **av;

    i = 0;
    av = ft_split(value, '=');
    if (!av)
        return;

    i = env_compare(*env, av, i);
    if ((*env)[i] == NULL)
        *env = ms_matrix_add_line(*env, value); // Update `*env`
    else
    {
        free((*env)[i]);
        (*env)[i] = ft_strdup(value);
    }
    ft_free_tab(av);
}


// Free a dynamically allocated char ** array
void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

// Get value of an environment variable
char *ms_get_varenv(char **env, char *av)
{
    int i;
    char **split;
    char *var_env;

    i = 0;
    var_env = NULL;
    while (env[i] && !var_env)
    {
        split = ft_split(env[i], '=');
        if (ft_strcmp(split[0], av) == 0)
            var_env = ft_strdup(split[1]);
        else
            i++;
        ft_free_tab(split);
    }
    if (env[i] == NULL)
        return NULL;
    return var_env;
}

// Add new variable to env
char **ms_matrix_add_line(char **matrix, char *new_line)
{
    int i;
    char **new_matrix;

    i = 0;
    while (matrix[i])
        i++;

    new_matrix = malloc(sizeof(char *) * (i + 2));
    if (!new_matrix)
        return NULL;

    i = 0;
    while (matrix[i])
    {
        new_matrix[i] = ft_strdup(matrix[i]);
        i++;
    }
    new_matrix[i] = ft_strdup(new_line);
    i++;
    new_matrix[i] = NULL;

    ft_free_tab(matrix);
    return new_matrix;
}

// Get environment variable entry
char *ms_get_env(char **env, char *av)
{
    int i;
    char **split;

    i = 0;
    while (env[i])
    {
        split = ft_split(env[i], '=');
        if (ft_strcmp(split[0], av) == 0)
        {
            ft_free_tab(split);
            break;
        }
        i++;
        ft_free_tab(split);
    }
    if (env[i] == NULL)
        return NULL;
    return env[i];
}

// Manage SHLVL variable
void check_shlvl(char ***env)
{
    char *var, *value, *new_var;
    int shlvl;

    var = ms_get_env(*env, "SHLVL");
    if (!var)
    {
        *env = ms_matrix_add_line(*env, "SHLVL=1");
        return;
    }
    value = ms_get_varenv(*env, "SHLVL");
    if (!value || ft_isdigit(value[0]) == 0)
    {
        printf("Warning: invalid SHLVL value. Resetting to 1\n");
        free(value);
        *env = ms_matrix_add_line(*env, "SHLVL=1");
        return;
    }
    shlvl = ft_atoi(value);
    free(value);
    if (shlvl < 0)
        shlvl = 1;
    else
        shlvl++;
    value = ft_itoa(shlvl);
    new_var = ft_strjoin("SHLVL=", value);
    free(value);
    ms_set_env(env, new_var);
    free(new_var);
}

// Initialize environment
void ms_env_init(t_msh **msh, char **envp)
{
    int i;

    if (!envp)
    {
        fprintf(stderr, "Error: env is NULL\n");
        exit(EXIT_FAILURE);
    }
    *msh = malloc(sizeof(t_msh));
    if (!*msh)
    {
        fprintf(stderr, "msh malloc failed\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (envp[i])
        i++;

    (*msh)->ms_env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!(*msh)->ms_env)
    {
        perror("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (envp[i])
    {
        (*msh)->ms_env[i] = ft_strdup(envp[i]);
        i++;
    }
    (*msh)->ms_env[i] = NULL;

    check_shlvl(&(*msh)->ms_env);

    (*msh)->exit_code = 0;
    (*msh)->prev_exit = 0;
}
