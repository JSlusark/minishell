#ifndef EXEC_H
#define EXEC_H

/**************************************/
/*              STRUCTS               */
/**************************************/

typedef struct bld_in {
	char	*name;
	int		(*func)(char **ac);
	struct bld_in *next;
} bld_in;

typedef struct s_exec
{
    int fd [2];
    t_node_list *action;
    struct s_exec *next;
}
    t_exec;


/************************************************************/
/*                      FUNCTIONS                           */
/************************************************************/

/*******************ENV************************/
char	**ms_matrix_add_line(char **matrix, char *new_line);
void    ft_free_tab(char **tab);
int check_exit(t_node_list *node, t_msh *msh, char **av);
void    ms_env_init(t_msh **msh, char**envp);
char    *ms_get_env(t_msh *msh, char *av);
void    ms_set_env(t_msh *msh, char *value);

/******************BUILTINS********************/
void     exec_cd(t_node_list *node);
void     exec_pwd(t_node_list	*node_l);
int     exec_env(t_node_list	*node_l);
int     exec_exit(t_node_list	*node_l);
void	exec_echo (t_node_list	*node);
void		exec_export(char **av, t_node_list *node);
void		exec_unset (char **av, t_node_list *node);
# endif