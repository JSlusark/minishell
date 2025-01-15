/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:14 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/15 12:09:57 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
//list of tests:
//https://docs.google.com/spreadsheets/d/1AUQk0Nrnvj7-9RQHEaSSQJgBb0VGlHvQt78khxBv5UQ/edit?gid=1887111398#gid=1887111398

// void free_mock_tokens(t_tokens *head) {
// 	t_tokens *current = head;
// 	t_tokens *next;

// 	while (current != NULL)
// 	{
// 		next = current->next; // Store the next token
// 		free(current->value); // Free the duplicated string
// 		free(current);             // Free the current node
// 		current = next;            // Move to the next token
// 	}
// }

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
		// printf("TOKEN:%s", new_token->value);
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


void	collect_str(int *i, char *input, char quote, int *len, char *buff, int *last_quote)
{
	while (*i <= *last_quote) // echo "hello""" does not print error
	{
		// Check for variable expansion inside double quotes
		if (input[*i] == '$' && quote == '"') // Expand variable only inside double quotes
		{
			char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";
			int j = *i + 1; // Start after the '$'

			// Identify the variable name
			while (input[j] && !ft_strchr(not_env, input[j]))
			{
				j++;
			}
			// Expand the variable if it matches
			if (ft_strncmp(&input[*i + 1], "USER", j - *i - 1) == 0 &&
				(size_t)(j - *i - 1) == ft_strlen("USER")) // could do a while loop taht check ll env_var names and compares
			{
				const char *expansion = "jjs"; // Simulate expansion
				int exp_len = strlen(expansion);
				if (*len + exp_len >= 1023) // Prevent buffer overflow
				{
					printf("Error: Buffer overflow during variable expansion\n");
					return;
				}
				for (int k = 0; k < exp_len; k++)
				{
					buff[*len] = expansion[k];
					(*len)++;
				}
			}
			*i = j-1; // Move *i to the last character that matches the env_name
		}
		else if (input[*i] != quote) // Copy other characters except for quotes
		{
			// printf("HIT I after exp: %c at input[%d]\n", input[*i], *i);
			if (*len >= 1023) // Preventing buffer overflow
			{
				printf("Error: Buffer overflow in collect_str\n");
				return;
			}
			buff[*len] = input[*i];
			(*len)++;
		}
		(*i)++;
	}
}


bool	quote_closed(int *i, char *input, char quote, int *last_quote)
{
	int j = *i;
	int quote_n = 0;
	char *bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	bool peek_quote = false;
	while(input[j] != '\0')
	{
		if(input[j] == quote)
		{
			*last_quote = j;
			quote_n++;
			// printf("quote_n %d\n", quote_n);
		}
		else if(ft_strchr(bounds, input[j])) // once we reach a bound we check the n of quotes and type of bounds
		{
			if(quote_n % 2 == 0 ) // we avoid including bounds in str
			{
				// printf(COLOR_GREEN"QUOTES CLOSED with last quote i %d\n"COLOR_RESET, *last_quote);
				return(true);
			}
			else if(quote_n %2 != 0 && input[j] == ' ') // we avoid continuing checking quotes that inclus | and redir
			{
				int k = j;
				while(input[k] != '\0') // check if there are other quotes in the string
				{
					// printf("-C: %c\n", input[k]);
					if(input[k] == quote)
					{
						peek_quote = true;
						break;
					}
					k++;
				}
				if(peek_quote == false)
				{
					printf("Minishell: %c at input[%d] had no closure\n", input[j], j);
					// printf(COLOR_RED"QUOTES UNCLOSED with last quote i %d\n", *last_quote);
					return(false);
				}
			}
		}
		j++;
	}
	if(quote_n % 2 != 0)
	{
		// printf(COLOR_RED"QUOTES UNCLOSED with last quote i %d\n", *last_quote);
		printf("Minishell: %c at input[%d] had no closure\n", input[j-1], j-1);
		return(false);
	}
	// printf(COLOR_GREEN"QUOTES CLOSED with last quote i %d\n"COLOR_RESET, *last_quote);
	return(true);
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
		char buff[1024] = {0};
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
			if(ft_strchr(quotes, input[i]) && input[i] != '\0') // logic to create token within quotes
			{
				// CHECK QUOTEDARG
				int last_quote = 0;
				if (!quote_closed(&i, input, input[i], &last_quote))
				{
					// printf("Minishell: %c at input[%d] had no closure\n", input[i], i);
					return (NULL);
				}
				collect_str(&i, input, input[i], &len, buff, &last_quote);
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
				{
					if (len > 0)
					{
						append_token(&tokens, create_token(buff, ARG));
						// printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
					}
				}
			}
			else // logic to create token without quotes
			{
				// printf("%c", input[i]);
				buff[len] = input[i];
				len++;
				i++;
				if(input[i] == ' ' || input[i] == '\0' || ft_strchr(bounds, input[i]))
				{
					// as this is where i get the full printed token i should terminate and append here?
					buff[len] = '\0';
					if (len > 0)
					{
						append_token(&tokens, create_token(buff, ARG));
					}
					// printf(COLOR_YELLOW"<---- ARG LEN %d (parsing assigns later as cmd, arg or file)\n"COLOR_RESET, len);
				}
			}
		}
		// CHECK BOUNDS
		if(input[i] == '|')
		{
			int k = i + 1;
			if(input[k] == '|')
			{
				printf("||");
				// printf(COLOR_YELLOW"<---- OPERATOR\n"COLOR_RESET);
				printf("Minishell: error || operator are just for bonus\n");
				return(NULL);
				// i++; // wtf i have put that?
			}
			else
			{
				append_token(&tokens, create_token("|", PIPE));
				// printf("%c", input[i]);
				// printf(COLOR_YELLOW"<---- PIPE len 1\n"COLOR_RESET);
			}
		}
		else if(input[i] == '>') // use a while to understand if >> ?
		{
			int j = i + 1;
			if(input[j] != '\0' && input[j] == '>')
			{
				append_token(&tokens, create_token(">>", APPEND));
				// printf(">>");
				// printf(COLOR_YELLOW"<---- APPEND_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				append_token(&tokens, create_token(">", REDIR_OUT));
				// printf("%c", input[i]);
				// printf(COLOR_YELLOW"<---- IN_REDIR len 1\n"COLOR_RESET);
			}
		}
		else if(input[i] == '<') // use a while to understand if >> ?
		{
			int y = i + 1;
			if(input[y] != '\0' && input[y] == '<')
			{
				append_token(&tokens, create_token("<<", HEREDOC));
				// printf("<<");
				// printf(COLOR_YELLOW"<---- HEREDOC_REDIR len 2\n"COLOR_RESET);
				i++;
			}
			else
			{
				append_token(&tokens, create_token("<", REDIR_IN));
				// printf("%c", input[i]);
				// printf(COLOR_YELLOW"<---- OUT_REDIR len 1\n"COLOR_RESET);
			}
		}
		if(input[i] != '\0')
			i++;
	}
	return(tokens); // <- return error as this
}
