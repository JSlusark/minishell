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

void remove_env(char *var, t_node_list *node)
{
    int index;

    index = find_env_index(node->msh->ms_env, var);
    if (index != -1)
    {
        ms_remove_line(node->msh, index);
    }
}

void    handle_unset (char **av, t_node_list *node)
{
    /*
        da jess:
        - quando unset non trova la env var o ha 0 args l'exit code e' sempre 0, perche' semplicemente non succede nulla
        - unset puo' avere piu' args, rimuove solo le env esistenti
     */
    int i;

    i = 0;
    if(node->cmd->args) // important to avoid seg fault if args are NULL
    {
        while(node->cmd->args[i])
        {
            remove_env(av[i], node);
            i++;
        }
    }
}
