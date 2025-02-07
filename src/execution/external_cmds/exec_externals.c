/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:52:18 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/07 09:21:10 by jslusark         ###   ########.fr       */
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
	while (envp[i] && ft_strnstr (envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	envp_paths = ft_split (envp[i] + 5, ':');
	if (!envp_paths)
		return (NULL);
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

int checkandexec (char **path, char ***cmds, t_msh *msh, t_cmd *cmd)
{
	struct stat sb;

	if (!*path)
	{
        write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": command not found\n", 20);
		free_results(*cmds);
		return (127);
	}
	if (stat(*path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
		write(2, path, ft_strlen(*path));
		write(2, ": Is a directory\n", 17);
		free(*path);
		return (126);
    }
	if (access(*path, F_OK) == -1)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": ", 2);
		// Jess: we need the error message here
		perror("");
		return (127);
	}
	if (access(*path, X_OK) == -1)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": ", 2);
		// Jess: we need the error message here
		perror("");
		return (126);
	}
	if (execve(*path, *cmds, msh->ms_env) == -1)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": ", 2);
		// Jess: we need the error message here
		perror("");
		return (127);
	}
	return (1);
}

int	exec_external(t_cmd *cmd, t_msh *msh)
{
	char	**cmds;
	char	*path;
	int exit_code;

	cmds = get_cmds(cmd);
	if (!cmds)
	{
		return (1);
	}
	if(strchr(cmds[0], '/') != NULL)
		path = cmds[0];
	else
		path = find_path (cmds[0], msh->ms_env);
	exit_code = checkandexec(&path, &cmds, msh, cmd);
	return (exit_code);
}
