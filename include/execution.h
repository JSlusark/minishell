/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:21:55 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 18:26:26 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/**************************************/
/*              STRUCTS               */
/**************************************/

typedef struct s_exec
{
	int				fd [2];
	t_node_list		*action;
	struct s_exec	*next;
}	t_exec;

/************************************************************/
/*                      FUNCTIONS                           */
/************************************************************/

/*******************EXEC***********************/
int		count_nodes(t_node_list	*node_list);
int		find_ext_cmd(t_node_list *node);
int		find_builtin(t_node_list	*node);
int		check_cmds(t_node_list *node_list);
int		close_wait_free(int **pipes, int node_amount, int last_pid);

/*******************ENV************************/
void	ms_env_init(t_msh **msh, char **envp);
void	init_env_vars(char ***env, char **envp);
void	check_shlvl(char ***env);
bool	found_shlvl_value(char ***env, char **value);
void	ms_set_env(char ***env, char *value);
char	*ms_get_env(char **env, char *av);
char	**ms_matrix_add_line(char **matrix, char *new_line);
char	*ms_get_varenv(char **env, char *av);
void	ft_free_tab(char **tab);
int		env_compare(char **env, char **av, int i);

/****************REDIRECTIONS*******************/
int		set_redirection(t_node_list *node);
char	*handle_heredoc(t_node_list *node);

/******************BUILTINS********************/
int		exec_builtin(t_node_list	*node_list);
int		exec_cd(t_node_list *node);
int		handle_pwd(t_node_list *node);
int		handle_env(t_node_list	*node_l);
int		exec_exit(t_node_list *node);
int		handle_echo(t_node_list *node);
void	exec_unset(char **av, t_node_list *node);
void	exec_export(char **av, t_node_list *node);
void	print_exported(char **env);
void	print_exp_error(const char *identifier);
void	sort_env_vars(char **env);

/******************EXTERNAL********************/
int		exec_external(t_cmd *cmd, t_msh *msh);
int		exec_child(t_node_list *node, int **pipe,
			int node_amount, int position);
char	*find_path(char *cmd, char **envp);

/********************PIPES**********************/
int		**pipe_init(int n_pipes);
void	close_pipes(int **pipes, int n);
void	set_pipe_ends(int **pipes, int position, int n_pipe);
void	free_pipes(int **pipes, int n);
void	wait_pids(pid_t *pids, int n_pids);

/********************SIGNALS**********************/
extern int	g_sig;
void	handle_eof(t_msh *msh);
void	ctrl_c(int sig);
void	back_slash(int sig);
void	restore_prompt(int sig);
void	run_signals(int sig, t_msh *t_msh);

#endif
