// #include "../../../include/minishell.h"


// static int find_env_index(char **env, char *var)
// {
//     int     i;
//     char    **split;

//     i = 0;
//     while (env[i])
//     {
//         split = ft_split(env[i], '=');
//         if (ft_strcmp(split[0], var) == 0)
//         {
//             ft_free_tab(split);
//             return i;
//         }
//         ft_free_tab(split);
//         i++;
//     }
//     return -1;
// }

// char **ms_remove_line(char **matrix, int index)
// {
//     int     i;
//     int     j;
//     char    **new_matrix;

//     i = 0;
//     while (matrix[i])
//         i++;
//     new_matrix = malloc(sizeof(char *) * i);
//     if (!new_matrix)
//         return NULL;
//     i = 0;
//     j = 0;
//     while (matrix[i])
//     {
//         if (i != index)
//         {
//             new_matrix[j] = ft_strdup(matrix[i]);
//             j++;
//         }
//         i++;
//     }
//     new_matrix[j] = NULL;
//     ft_free_tab(matrix);
//     return new_matrix;
// }

// int ms_unset_env(char **env, char *var)
// {
//     int index;

//     index = find_env_index(env, var);
//     if (index != -1)
//     {
//         g_msh.env = ms_remove_line(env, index);
//         return (0);
//     }
//     return(1);
// }

// int    handle_unset(char **av)
// {
//     if (!av[1])
//     {
//         fprintf (stderr, "unset: missing argument\n");
//         return (EXIT_FAILURE);
//     }
//     if ((ms_unset_env(g_msh.env, av[1])) != 0)
//     {
//         perror ("unset");
//         return (EXIT_FAILURE);
//     }
//     return (EXIT_SUCCESS);
// }