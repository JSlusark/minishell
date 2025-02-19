/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:12:33 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/19 17:38:16 by stdi-pum         ###   ########.fr       */
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

bool    add_line_to_doc(char *line, t_redir *redir, t_exec *exec, char **doc)
{
    char    *temp;
    if (!line)
        return (false);
    line = expanded_line(line, exec->msh);
    if (strcmp(line, redir->target) == 0)
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

char	*exec_heredoc(t_redir *redir, t_exec *exec)
{
	char    *line;
	char    *doc;
	doc = NULL;
	run_signals(3, NULL);

	while (1)
	{
		if (g_sig == SIGINT)
		{
			exec->msh->exit_code = 130;
			g_sig = 0;
			break ;
		}
		line = readline("> ");
		if (!add_line_to_doc(line, redir, exec, &doc))
			break ;
	}
	if(doc == NULL)
		{doc = ft_strdup("");}

	// write(1, doc, ft_strlen(doc));
	//feed_heredoc_to_pipe(doc);
	//free(doc);
	return (doc);
}

// char *handle_heredoc(t_redir *redir, t_exec *exec)
// {
// 	t_redir *temp;
// 	char *doc;
	
// 	doc = NULL;
// 	temp = redir;
// 	while (redir)
// 	{
// 		if(redir->type == HEREDOC)
// 		{	
// 			if(doc != NULL)
// 				free(doc);
// 			doc = exec_heredoc(redir, exec);
// 		}
// 		temp = redir;
// 		redir = redir->next;
// 		free(temp->target);
// 		free(temp);
// 	}
// 	return (doc);
// }

void	handle_heredoc(t_node_list *node, int *heredoc_pipe, t_exec *exec)
{
    char *doc;

    t_redir *current_redir;
    t_redir *prev_redir;

    current_redir = node->redir;
    prev_redir = NULL;
	doc = NULL;
    while (current_redir)
    {
        if (current_redir->type == HEREDOC)
        {
			if(doc != NULL)
				free(doc);
            doc = exec_heredoc(current_redir, exec);
            if (pipe(heredoc_pipe) == -1)
            {
                perror("pipe");
                free(doc);
                return ;
            }
            write(heredoc_pipe[1], doc, ft_strlen(doc));
            close(heredoc_pipe[1]);
            free(doc);

            // Remove the heredoc node from the redir list
            if (prev_redir)
                prev_redir->next = current_redir->next;
            else
                node->redir = current_redir->next;

            t_redir *temp_redir = current_redir;
            current_redir = current_redir->next;
            free(temp_redir->target);
            free(temp_redir);
        }
        else
        {
            prev_redir = current_redir;
            current_redir = current_redir->next;
        }
    }
}