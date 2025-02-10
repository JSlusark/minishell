/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:12:33 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/08 19:33:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*expanded_line(char *line, t_msh *msh)
{
	int		i;
	char	*buff;
	int		j;

	j = 0;
	i = 0;
	buff = malloc(ft_strlen(line) + 1024);
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			collect_expansion(line, &i, buff, msh);
			i++;
			j = ft_strlen(buff);
		}
		buff[j] = line[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	return (buff);
}

bool	add_line_to_doc(char *line, t_node_list *node, char **doc)
{
	char	*temp;

	if (!line)
		return (false);
	line = expanded_line(line, node->msh);
	if (strcmp(line, node->redir->target_name) == 0)
	{
		free(line);
		return (false);
	}
	if (*doc == NULL)
		*doc = ft_strdup(line);
	else
	{
		temp = ft_strjoin(*doc, line);
		free(*doc);
		*doc = temp;
	}

	temp = ft_strjoin(*doc, "\n");
	free(*doc);
	*doc = temp;

	free(line);
	return (true);
}


char	*handle_heredoc(t_node_list *node)
{
	char	*line;
	char	*doc;

	doc = NULL;
	run_signals(3, NULL);
	while (1)
	{
		if (g_sig == SIGINT)
		{
			node->msh->exit_code = 130;
			g_sig = 0;
			break ;
		}
		line = readline("> ");
		if (!add_line_to_doc(line, node, &doc))
			break ;
	}
	if (!doc)
		doc[0] = '\0';
	return (doc);
}