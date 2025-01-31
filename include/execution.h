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

/*******************EXEC***********************/
int		count_nodes(t_node_list	*node_list);
int		find_ext_cmd(t_node_list *node);
int		find_builtin(t_node_list	*node);
int		check_cmds(t_node_list *node_list);
int		close_wait_free(int **pipes, int node_amount);

/*******************ENV************************/
char	**ms_matrix_add_line(char **matrix, char *new_line);
void    ft_free_tab(char **tab);
void    ms_env_init(t_msh **msh, char**envp);
char    *ms_get_env(t_msh *msh, char *av);
void    ms_set_env(t_msh *msh, char *value);

/****************REDIRECTIONS*******************/
void set_redirection(t_node_list *node);

/******************BUILTINS********************/
int 	exec_builtin(t_node_list	*node_list);
int     exec_cd(t_node_list *node);
int     handle_pwd(t_node_list *node);
int     handle_env(t_node_list	*node_l);
int     exec_exit(t_node_list *node);
int		handle_echo (t_node_list	*node);
void    exec_export(char **av, t_node_list *node);
void    exec_unset (char **av, t_node_list *node);

/******************EXTERNAL********************/
int		exec_external(t_cmd *cmd, t_msh *msh);
int		exec_child(t_node_list *node, int **pipe, int node_amount, int position);
char	*find_path(char *cmd, char **envp);

/********************PIPES**********************/
int		**pipe_init(int n_pipes);
void	close_pipes(int **pipes, int n);
void    set_pipe_ends(int **pipes, int position, int n_pipe);
void    free_pipes(int **pipes, int n);
void	wait_pids(pid_t *pids, int n_pids);

/********************SIGNALS**********************/
#include <termios.h>
void	handle_eof(t_msh *msh);
void	setup_signals(void);


# endif
