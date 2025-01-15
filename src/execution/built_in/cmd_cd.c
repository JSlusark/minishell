// #include "../../../include/minishell.h"

// void    set_pwd(char *av, char *c, char **ms_env)
// {
//     char    *string;

//     string = ft_strjoin(av, c);
//     ms_set_env (ms_env, string);
//     free (string);
// }

// int    handle_cd(t_node_list *node)
// {
//     char    cwd[1024];
//     char    *avs;

//     avs = node->args->value;//token dopo cd (Ex. src con cd/src)
//     if (avs == NULL)
//     {
//         avs = ms_get_env (node->t_msh->ms_env, "HOME") + 5;
//         if ((avs - 5) == NULL)
//         {
//             printf ("cd: HOME not set\n");
//             return (1);
//         }
//     }
//     getcwd(cwd, sizeof(cwd));
//     if (chdir(avs) == -1)
//     {
//         if (avs[0] == '\0')
//             return (1);
//         ft_putstr_fd ("cd: ", 2);
//         ft_putstr_fd (avs, 2);
//         ft_putendl_fd (": no such file or dir", 2);
//         return (1);
//     }
//     set_pwd ("OLDPWD=", cwd);
//     getcwd(cwd, sizeof(cwd));
//     set_pwd("PWD=", cwd, node->t_msh->ms_env);
//     return (0);
// }

// char *read_input(void)
// {
//     char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//     {
//         char prompt[1064];
//         int i = 0;
//         while (cwd[i] != '\0')
//         {
//             prompt[i] = cwd[i];
//             i++;
//         }
//         prompt[i++] = ' ';
//         prompt[i++] = 'M';
//         prompt[i++] = 'e';
//         prompt[i++] = 's';
//         prompt[i++] = 't';
//         prompt[i++] = 'e';
//         prompt[i++] = 'p';
//         prompt[i++] = 'u';
//         prompt[i++] = 'm';
//         prompt[i++] = '>';
//         prompt[i++] = ' ';
//         prompt[i] = '\0';

//         char *line = readline(prompt);
//         if (line && *line)
//             add_history(line);
//         return line;
//     }
//     else
//     {
//         perror("getcwd() error");
//         return NULL;
//     }
// }