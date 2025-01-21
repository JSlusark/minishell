#include "../../../include/minishell.h"


static int find_env_index(char **env, char *var)
{
    int     i;
    char    **split;

    i = 0;
    while (env[i])
    {
        split = ft_split(env[i], '=');
        if (ft_strcmp(split[0], var) == 0)
        {
            ft_free_tab(split);
            return i;
        }
        ft_free_tab(split);
        i++;
    }
    return -1;
}

int	ms_remove_line(t_msh *msh, int index)
{
    int     i;
    int     j;
    char    **new_matrix;

    i = 0;
    while (msh->ms_env[i])
        i++;
    new_matrix = malloc(sizeof(char *) * i);
    if (!new_matrix)
        return 1;
    i = 0;
    j = 0;
    while (msh->ms_env[i])
    {
        if (i != index)
        {
            new_matrix[j] = ft_strdup(msh->ms_env[i]);
            j++;
        }
        i++;
    }
    new_matrix[j] = NULL;
    ft_free_tab(msh->ms_env);
    msh->ms_env = new_matrix;
	return 0;
}

int ms_unset_env(char *var, t_node_list *node)
{
    int index;

    index = find_env_index(node->msh->ms_env, var);
    if (index != -1)
    {
        ms_remove_line(node->msh, index);
        return (0);
    }
    return(1);
}

void    handle_unset (char **av, t_node_list *node)
{
    if (!av[0])
    {
        printf ("unset: not enough arguments\n");//da rivedere implementazione exit_code
        node->msh->exit_code = 1;//da rivedere implementazione exit_code
    }
    if ((ms_unset_env(av[0], node)) != 0)
    {
        perror ("unset");//da rivedere implementazione exit_code
        node->msh->exit_code = 1;//da rivedere implementazione exit_code
    }
}