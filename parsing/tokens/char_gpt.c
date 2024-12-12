/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_gpt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:47:30 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/12 14:47:47 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	quote_closed(int i, char *input, char quote)
{
	int j = i;
	j++;
	while(input[j] && input[j] != quote && input[i] != '\0')
		j++;
	if(input[j] == quote)
		return(true);
	return(false);
}
t_tokens *create_token(const char *value, int type)
{
    t_tokens *new_token = malloc(sizeof(t_tokens));
    if (!new_token)
        return NULL;
    new_token->value = strdup(value);
    if (!new_token->value)
    {
        free(new_token);
        return NULL;
    }
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

void append_token(t_tokens **head, t_tokens *new_token)
{
    if (!*head)
    {
        *head = new_token;
        return;
    }
    t_tokens *current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

void free_tokens(t_tokens *head)
{
    t_tokens *current;
    while (head)
    {
        current = head;
        head = head->next;
        free(current->value);
        free(current);
    }
}

// Updated collect_str Function

void collect_str(int *i, char *input, char quote, int *len, t_tokens **tokens)
{
    char buffer[1024]; // Buffer for token value
    // int start = *i;
    int j = 0;

    (*i)++;
    while (input[*i] != '\0' && input[*i] != quote)
    {
        if (input[*i] == '$' && quote == '"') // Expand variables only in double quotes
        {
            char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";
            int var_start = *i + 1;
            while (input[var_start] && !ft_strchr(not_env, input[var_start]))
                var_start++;

            if (ft_strncmp(&input[*i + 1], "USER", var_start - *i - 1) == 0)
            {
                strcat(buffer, "jjs");
                j += 3;
            }
            *i = var_start;
        }
        else
        {
            buffer[j++] = input[*i];
            (*i)++;
        }
    }
    if (input[*i] == quote)
        (*i)++;
    buffer[j] = '\0';
    append_token(tokens, create_token(buffer, ARG));
    *len += j;
}

// Updated return_tokens Function

t_tokens *return_tokens(char *input)
{
    int i = 0;
    char *invalid = ";#&,`*~\\";
    char *bounds = "|>< ";
    char *quotes = "\"'";
    t_tokens *tokens = NULL;

    while (input[i] != '\0')
    {
        char buffer[1024];
        int len = 0;

        // CHECK INVALID
        if (ft_strchr(invalid, input[i]))
        {
            printf("Minishell: invalid token %c at input[%d]\n", input[i], i);
            free_tokens(tokens);
            return NULL;
        }

        // CREATE ARGS
        if (!ft_strchr(bounds, input[i]) && input[i] != '\0')
        {
            while (!ft_strchr(bounds, input[i]) && input[i] != '\0')
            {
                if (ft_strchr(quotes, input[i]))
                {
                    if (!quote_closed(i, input, input[i]))
                    {
                        printf("Minishell: %c at input[%d] had no closure\n", input[i], i);
                        free_tokens(tokens);
                        return NULL;
                    }
                    collect_str(&i, input, input[i], &len, &tokens);
                }
                else
                {
                    buffer[len++] = input[i++];
                }
            }
            buffer[len] = '\0';
            if (len > 0)
                append_token(&tokens, create_token(buffer, ARG));
        }

        // CHECK BOUNDS
        if (input[i] == '|')
        {
            append_token(&tokens, create_token("|", PIPE));
            i++;
        }
        else if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                append_token(&tokens, create_token(">>", APPEND));
                i += 2;
            }
            else
            {
                append_token(&tokens, create_token(">", REDIR_OUT));
                i++;
            }
        }
        else if (input[i] == '<')
        {
            if (input[i + 1] == '<')
            {
                append_token(&tokens, create_token("<<", HEREDOC));
                i += 2;
            }
            else
            {
                append_token(&tokens, create_token("<", REDIR_IN));
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    return tokens;
}
