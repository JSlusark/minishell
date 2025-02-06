/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:26:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/06 16:53:06 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	set_pwd(char *av, char *c, t_msh *msh)
{
	char	*string;

	string = ft_strjoin(av, c);
	ms_set_env (msh, string);
	free (string);
}

int    exec_cd(t_node_list *node)
{
	char    cwd[1024];
	char    *avs;

	avs = NULL;
	if (!node->cmd->args)
	{
		printf("cd has no args\n");
		avs = ms_get_env (node->msh, "HOME") + 5;
		if ((avs - 5) == NULL)
		{
			printf ("cd: HOME not set\n");
			return (1);
		}
	}
	else
	{
		int i = 0;
		printf("cd has args");
		while(node->cmd->args[i] != NULL)
		{
			printf("arg: %s\n", node->cmd->args[i]);
			i++;
		}
		printf("arg total: %d\n", i);
		if(i > 1)
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			node->msh->exit_code = 1;
			return (1);
		}
		avs = node->cmd->args[0];
		getcwd(cwd, sizeof(cwd));
		if (chdir(avs) == -1)
		{
			if (avs[0] == '\0')
				return (1);
			ft_putstr_fd ("cd: ", 2);
			ft_putstr_fd (avs, 2);
			ft_putendl_fd (": No such file or directory", 2);
			node->msh->exit_code= 1;
			return (1);
		}
		set_pwd ("OLDPWD=", cwd, node->msh);
		getcwd(cwd, sizeof(cwd));
			set_pwd("PWD=", cwd, node->msh);
	}
	return (0);
}

