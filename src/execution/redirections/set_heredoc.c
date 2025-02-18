/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:12:33 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/18 16:06:38 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
char    *handle_heredoc(t_node_list *node)
{
    char    *line;
    char    *doc;
    doc = NULL;
    run_signals(3, NULL);
    while (1)
    {
        //node->msh->in_heredoc = true;
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
        doc = ft_strdup("");
    return (doc);
}