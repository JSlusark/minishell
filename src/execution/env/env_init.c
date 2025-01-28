#include "../../../include/minishell.h"



int env_compare(char **env, char **av, int i)
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

void    ms_set_env(t_msh *msh, char *value)
{
    int     i;
    char    **av;

    i = 0;
    av = ft_split (value, '='); //if split does not find '=', av [0] == nome della variabile.
    i = env_compare(msh->ms_env, av, i);
    if (msh->ms_env[i] == NULL)
        msh->ms_env = ms_matrix_add_line(msh->ms_env, value);
    else
    {
        free (msh->ms_env[i]);
        msh->ms_env[i] = ft_strdup (value);
    }
    ft_free_tab (av);
}

void    ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free (tab[i]);
        i++;
    }
    free (tab);
}

char    *ms_get_varenv(char **env, char *av)
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

char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
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
	return (new_matrix);
}

char    *ms_get_env(t_msh *msh, char *av)
{
    int     i;
    char    **split;

    i = 0;
    while (msh->ms_env[i])
    {
        split = ft_split (msh->ms_env[i], '=');
        if (ft_strcmp(split[0], av) == 0)
        {
            ft_free_tab (split);
            break ;
        }
        else
            i++;
        ft_free_tab (split);
    }
    if (msh->ms_env[i] == NULL)
        return (NULL);
    return (msh->ms_env[i]);
}

void    check_shlvl(t_msh *msh)
{
    char    *var;
    char    *value;
    int     shlvl;
    char    *new_var;

    var = ms_get_env (msh, "SHLVL");
    if (!var)
    {
        msh->ms_env = ms_matrix_add_line(msh->ms_env, "SHLVL=1");
        return ;
    }
    value = ms_get_varenv (msh->ms_env, "SHLVL");
    if (!value || ft_isdigit(value[0]) == 0)
    {
        printf("Warning: invalid SHLVL value. Resetting to 1\n");
        free (value);
        msh->ms_env = ms_matrix_add_line (msh->ms_env, "SHLVL=1");
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
    ms_set_env (msh, new_var);
    free (new_var);
}

void    ms_env_init(t_msh **msh, char **envp)
{
    int i;

    i = 0;
    if (!envp)
    {
        fprintf(stderr, "Error: env is NULL\n");
        exit(EXIT_FAILURE);
    }
    *msh = malloc(sizeof(t_msh));
    if (msh == NULL)
    {
        fprintf(stderr, "msh malloc failed\n");
        exit(EXIT_FAILURE);
    }
    while (envp[i])
        i++;
    (*msh)->ms_env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!(*msh)->ms_env)
    {
        perror ("malloc failed\n");
        exit (EXIT_FAILURE);
    }
    i = 0;
    while (envp[i])
    {
        (*msh)->ms_env[i] = ft_strdup (envp[i]);
        i++;
    }
    (*msh)->ms_env[i] = NULL;
    check_shlvl((*msh));
    (*msh)->exit_code = 0;
    (*msh)->prev_exit = 0;
}