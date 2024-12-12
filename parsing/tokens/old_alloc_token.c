/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_alloc_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:11 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/12 16:29:14 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void free_tokens(t_tokens *head)
// {
//     t_tokens *current;
//     while (head)
//     {
//         current = head;
//         head = head->next;
//         free(current->value);
//         free(current);
//     }
// }

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

void	collect_str(int *i, char *input, char quote, int *len, char *buff)
{
	// printf("%c %c\n", input[*i], quote);
	while(input[*i] != '\0') // echo "hello""" does not print error
	{
		printf("C:%c I: %i\n", input[*i], *i);
		if(input[*i] == quote)
			(*i)++;
		else
		{
			if (input[*i] == '$' && quote == '"') // Expand variable only inside double quotes
			{
				char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";
				int j = *i + 1; // Start after the '$'
				while (input[j] && !ft_strchr(not_env, input[j]))
				{
					j++;
				}
				// Check if the substring matches "USER"
				if (ft_strncmp(&input[*i + 1], "USER", j - *i - 1) == 0 &&
					(size_t)(j - *i - 1) == ft_strlen("USER"))
				{
					printf("jjs"); // Replace with the actual expansion
					*len += 3;    // Add the length of "jjs" to the token length
					// while jjs buff[i++]= buff[len++];
				}
				else
				{
					// Print the variable name literally if no match
					while (*i < j)
					{
						// printf("%c", input[*i]);
						buff[*i++]= buff[*len++]; /// CHECK IF I AND LEN
						// (*i)++;
						// (*len)++;
					}
				}
				*i = j; // Move *i past the variable name
			}
			else
			{
				// Print non-variable characters
				printf("%c", input[*i]);
				buff[*i++]= buff[*len++]; /// CHECK IF I AND LEN
				// (*len)++; // <----- len is effed up when non existing env var
				// (*i)++;
			}
		}

	}
}

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

t_tokens *return_tokens(char *input)
{
	int i = 0;
	char *invalid = ";#&,`*~\\";  // seen outside string also && $(..)
	char *bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	char *quotes = "\"'";  // anything inside quotes is considered an arg, for expansion we check if token is D STRING and if it has $ inside

	t_tokens *tokens = NULL;
	// t_tokens *token = NULL;


	while (input[i] != '\0')
	{
		char buff[1024];
		int len = 0;
		int h = i;

		// CHECK INVALID FUNCTION
		while(ft_strchr(invalid, input[h]))
		{
			h++;
			if(input[h] == '\0' || ft_strchr(bounds, input[h])) // problem when followed by other invalid symbls
			{
				printf("Minishell: invalid token %c at input[%d]\n", input[i], i); // why wrong input
				return(NULL);
			}
			if(!ft_strchr(invalid, input[h]))
				break;
		}

		// IF NOT INVALID, CREATE ARGS
		while(!ft_strchr(bounds, input[i]) && input[i] != '\0') // this grabs leters attached together as tokens, even when we have strings
		{
			if(ft_strchr(quotes, input[i]) && input[i] != '\0')
			{
				// CHECK QUOTEDARG
				if (!quote_closed(i, input, input[i]))
				{
					printf("Minishell: %c at input[%d] had no closure\n", input[i], i);
					return (NULL);
				}
				collect_str(&i, input, input[i], &len, buff);
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
				{
					append_token(&tokens, create_token(buff, ARG));
					printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
				}
			}
			else
			{
				printf("%c", input[i]);
				buff[len++] = input[i++];
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
				{
					// as this is where i get the full printed token i should terminate and append here?
					buff[len] = '\0';
					if (len > 0)
					{
						append_token(&tokens, create_token(buff, ARG));
					}
					printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
				}
			}
		}
		// CHECK BOUNDS
		if(input[i] == '|')
		{
			int k = i + 1;
			if(input[k] != '\0' && input[k] == '|')
			{
				printf("||");
				printf(COLOR_YELLOW"<---- OPERATOR\n"COLOR_RESET);
				printf("Minishell: error || operator are just for bonus\n");
				return(NULL);
				// i++; // wtf i have put that?
			}
			else
			{
				append_token(&tokens, create_token(buff, PIPE));
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- PIPE len 1\n"COLOR_RESET);
			}
		}
		if(input[i] == '>') // use a while to understand if >> ?
		{
			int j = i + 1;
			if(input[j] != '\0' && input[j] == '>')
			{
				append_token(&tokens, create_token(">>", APPEND));
				printf(">>");
				printf(COLOR_YELLOW"<---- APPEND_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				append_token(&tokens, create_token(">", REDIR_OUT));
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- IN_REDIR len 1\n"COLOR_RESET);
			}
		}
		if(input[i] == '<') // use a while to understand if >> ?
		{
			int y = i + 1;
			if(input[y] != '\0' && input[y] == '<')
			{
				append_token(&tokens, create_token("<<", HEREDOC));
				printf("<<");
				printf(COLOR_YELLOW"<---- HEREDOC_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				append_token(&tokens, create_token("<", REDIR_IN));
				printf("%c", input[i]);
				printf(COLOR_YELLOW"<---- OUT_REDIR len 1\n"COLOR_RESET);
			}
		}
		if(input[i] != '\0')
			i++;
	}
	return(tokens); // <- return error as this
}
