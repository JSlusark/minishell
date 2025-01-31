/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:52:18 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/01/31 14:49:20 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_results(char **results)
{
	int	i;

	i = 0;
	while (results[i])
	{
		free(results[i++]);
	}
	free(results);
}

static char	*ft_eiterate(char **path, char **envp_paths, char *cmd)
{
	char	*add_slash;
	int		i;

	i = 0;
	while (envp_paths[i])
	{
		add_slash = ft_strjoin (envp_paths[i], "/");
		if (add_slash == NULL)
			return (NULL);
		(*path) = ft_strjoin (add_slash, cmd);
		if (*path == NULL)
			return (NULL);
		free(add_slash);
		if (access (*path, X_OK) == 0)
			return (*path);
		free(*path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**envp_paths;
	char	*path;
	int		i;

	i = 0;
	if(strchr(cmd, '/') != NULL)
	{
		path = ft_strdup(cmd);
		return (path);
	}
	while (envp[i] && ft_strnstr (envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		return (NULL);
	}
	envp_paths = ft_split (envp[i] + 5, ':');
	if (!envp_paths)
	{
		return (NULL);
	}
	path = ft_eiterate(&path, envp_paths, cmd);
	free_results(envp_paths);
	if (path != NULL)
		return (path);
	return (NULL);
}

char	**get_cmds(t_cmd *cmd)
{
	char	**cmds;
	int		i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
		cmds = malloc(sizeof(char*) * (i + 2));
		if(cmds == NULL)
			return (NULL);
		cmds[0] = ft_strdup(cmd->cmd);
		i = 1;
		while (cmd->args[i - 1])
		{
			cmds[i] = ft_strdup(cmd->args[i - 1]);
			i++;
		}
		cmds[i] = NULL;
	}
	else
	{
		cmds = malloc(sizeof(char*) * 2);
		if(cmds == NULL)
			return (NULL);
		cmds[0] = ft_strdup(cmd->cmd);
		cmds[1] = NULL;
	}
	return (cmds);
}

int	exec_external(t_cmd *cmd, t_msh *msh)
{
	char	**cmds;
	char	*path;

	cmds = get_cmds(cmd);
	if (!cmds)
	{
		return (1);
	}
	path = find_path (cmds[0], msh->ms_env);
	if (!path)
	{
		printf("No such file or directory\n");
		//write(1, "No such file or directory\n", 27);
		free_results(cmds);
		return (126);
	}
	if (access(path, X_OK) == -1)
	{
		printf("No permission to file or directory\n");
		free_results(cmds);
		free(path);
		return (126);
	}
	if (execve(path, cmds, msh->ms_env) == -1)
	{
		printf("%s: command not found\n", cmd->cmd);
		//write(1, "command not found\n", 19);
		return (127);
	}
	return (0);
}

// int	open_file(char *argv, int i)
// {
// 	int	file;

// 	file = 0;
// 	if (i == 0)
// 		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	else if (i == 1)
// 		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	else if (i == 2)
// 		file = open(argv, O_RDONLY, 0777);
// 	if (file == -1)
// 		error();
// 	return (file);
// }

// void	error(void)
// {
// 	perror("\033[31mError");
// 	exit(EXIT_FAILURE);
// }
