/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:01:14 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/27 18:14:53 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../../include/minishell.h"

/*
	JESS NOTES:
	0. when we move to the dire
	1. updating msh->envar->$PWD might be a problem when we have pipes no?
	2. We should check also permissions when executing no?
	3. we have to see if the directory exist? or if it's even a directory?
 */

void exec_cd(t_node_list *node)
{
	// char cwd[1024];
	char *new_dir = NULL;
	(void) new_dir;

	// Get the directory to change to
	if (node->cmd->args)
	{
		new_dir = node->cmd->args[0]; // First argument after `cd`
		printf("Moving to /%s\n", node->cmd->args[0]);
	}
	// else
	// {
	// 	// If no argument is given, fallback to HOME
	// 	char *home = ms_get_env(node->t_msh->ms_env, "HOME");
	// 	if (!home)
	// 	{
	// 		fprintf(stderr, "cd: HOME not set\n");
	// 		return 1;
	// 	}
	// 	new_dir = home;
	// }

	// // Save the current directory in `OLDPWD`
	// if (getcwd(cwd, sizeof(cwd)) == NULL)
	// {
	// 	perror("cd: getcwd");
	// 	return 1;
	// }
	// set_env_var("OLDPWD=", cwd, node->t_msh->ms_env);

	// // Attempt to change directory
	// if (chdir(new_dir) == -1)
	// {
	// 	fprintf(stderr, "cd: %s: No such file or directory\n", new_dir);
	// 	return 1;
	// }

	// // Update `PWD` in environment
	// if (getcwd(cwd, sizeof(cwd)) != NULL)
	// {
	// 	set_env_var("PWD=", cwd, node->t_msh->ms_env);
	// }
	// else
	// {
	// 	perror("cd: getcwd");
	// 	return 1;
	// }
}


// // OLD FROM STEFANO
// void    set_pwd(char *av, char *c, char **ms_env)
// {
// 	char    *string;

// 	string = ft_strjoin(av, c);
// 	ms_set_env (ms_env, string);
// 	free (string);
// }

// int    exec_cd(t_node_list *node)
// {
// 	char    cwd[1024];
// 	char    *avs;

// 	avs = node->args->value;//token dopo cd (Ex. src con cd/src)
// 	if (avs == NULL)
// 	{
// 		avs = ms_get_env (node->t_msh->ms_env, "HOME") + 5;
// 		if ((avs - 5) == NULL)
// 		{
// 			printf ("cd: HOME not set\n");
// 			return (1);
// 		}
// 	}
// 	getcwd(cwd, sizeof(cwd));
// 	if (chdir(avs) == -1)
// 	{
// 		if (avs[0] == '\0')
// 			return (1);
// 		ft_putstr_fd ("cd: ", 2);
// 		ft_putstr_fd (avs, 2);
// 		ft_putendl_fd (": no such file or dir", 2);
// 		return (1);
// 	}
// 	set_pwd ("OLDPWD=", cwd);
// 	getcwd(cwd, sizeof(cwd));
// 	set_pwd("PWD=", cwd, node->t_msh->ms_env);
// 	return (0);
// }

// char *read_input(void)
// {
// 	char cwd[1024];
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		char prompt[1064];
// 		int i = 0;
// 		while (cwd[i] != '\0')
// 		{
// 			prompt[i] = cwd[i];
// 			i++;
// 		}
// 		prompt[i++] = ' ';
// 		prompt[i++] = 'M';
// 		prompt[i++] = 'e';
// 		prompt[i++] = 's';
// 		prompt[i++] = 't';
// 		prompt[i++] = 'e';
// 		prompt[i++] = 'p';
// 		prompt[i++] = 'u';
// 		prompt[i++] = 'm';
// 		prompt[i++] = '>';
// 		prompt[i++] = ' ';
// 		prompt[i] = '\0';

// 		char *line = readline(prompt);
// 		if (line && *line)
// 			add_history(line);
// 		return line;
// 	}
// 	else
// 	{
// 		perror("getcwd() error");
// 		return NULL;
// 	}
// }