/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:12:33 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:02 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	feed_heredoc_to_pipe(char *doc)
{
	int	fd[2];
	(void)doc;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	// dup2(fd[0], STDIN_FILENO);
	// close(fd[0]);
	// write(fd[0], doc, ft_strlen(doc));
	// close(fd[1]);
	// close(fd[0]);
	// return (0);
	// write(fd[1], doc, ft_strlen(doc));
    // close(fd[1]);
    // // Reindirizza stdin alla pipe
    // if (dup2(fd[0], STDIN_FILENO) == -1)
    // {
    //     perror("dup2");
    //     close(fd[0]);
    //     return (-1);
    // }
    // close(fd[0]);
    return (0);
}

void    process_expansion_or_copy(char *line, int *i, char *buff, t_msh *msh)
{
    int j;
    j = ft_strlen(buff);
    if (line[*i] == '$')
    {
        collect_expansion(line, i, buff, msh);
        (*i)++;
    }
    else
    {
        buff[j] = line[*i];
        (*i)++;
        buff[j + 1] = '\0';
    }
}

char    *expanded_line(char *line, t_msh *msh)
{
    int     i;
    int     size;
    char    *buff;
    i = 0;
    size = ft_strlen(line) + 1024;
    buff = malloc(size);
    if (!buff)
        return (NULL);
    ft_bzero(buff, size);
    while (line[i] != '\0')
        process_expansion_or_copy(line, &i, buff, msh);
    return (buff);
}
bool    add_line_to_doc(char *line, t_node_list *node, char **doc)
{
    char    *temp;
    if (!line)
        return (false);
    line = expanded_line(line, node->msh);
    if (strcmp(line, node->redir->target) == 0)
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

char	*exec_heredoc(t_node_list *node)
{
	char    *line;
	char    *doc;
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
	if(doc == NULL)
		{doc = ft_strdup("");}

	// write(1, doc, ft_strlen(doc));
	//feed_heredoc_to_pipe(doc);
	//free(doc);
	return (doc);
}

char *handle_heredoc(t_node_list *node)
{
	t_redir *temp;
	char *doc;
	
	doc = NULL;
	temp = node->redir;
	while (node->redir)
	{
		if(node->redir->type == HEREDOC)
			doc = exec_heredoc(node);
		temp = node->redir;
		node->redir = node->redir->next;
		free(temp->target);
		free(temp);
	}
	return (doc);
}