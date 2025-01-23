/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:43:06 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/23 18:40:35 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *find_envar(char *var, char **env) // finds only the var, does not expand
{
	int i;
	char *var_content;
	i = 0;
	var_content = NULL;
	while (env[i])
	{
		if (strncmp(env[i], var, strlen(var)) == 0 && env[i][strlen(var)] == '=')
		{
			var_content = env[i] + strlen(var) + 1;
			break;
		}
		i++;
	}
	if (!env[i]) // if var does not exists it expans to null
		return (NULL);
	return ft_strdup(var_content);
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


void collect_str(int *i, char *input, char quote, int *len, char *buff, int *last_quote, t_msh *msh)
{
	while (*i <= *last_quote) // Process characters within the quoted string
	{
		// Check for variable expansion inside double quotes
		if (input[*i] == '$' && quote == '"') // Expand variables only inside double quotes
		{
			char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ "; // Characters not valid in variable names
			int j = *i + 1; // Start after the '$'

			// Check for $ followed by ?
			if (input[j] == '?')
			{
				char *exit_code_str = ft_itoa(msh->exit_code); // Convert exit code to string
				int exp_len = strlen(exit_code_str);
				if (*len + exp_len >= 1023) // Prevent buffer overflow
				{
					printf("Error: Buffer overflow during $? expansion\n");
					free(exit_code_str);
					return;
				}
				for (int k = 0; k < exp_len; k++) // Append the exit code string to the buffer
				{
					buff[*len] = exit_code_str[k];
					(*len)++;
				}
				free(exit_code_str); // Free the dynamically allocated exit code string
				*i = j + 1; // input[*] is ? so move past by j++;
				continue; // Skip the rest of the loop
			}

			// IF SHOULD BE ANY INVALID IS GUESS (echo "$'US'ER" comes $'US'ER)
			// Check for $ followed by space (ex: "? ", "? hello") or " (ex" "?")
			if (input[j] == ' ' || ft_strchr(not_env, input[j])) // $ does not expand if followed by space or not_env
			{
				if (*len + 1 >= 1023) // Prevent buffer overflow
				{
					printf("Error: Buffer overflow during $ expansion\n");
					return;
				}
				buff[*len] = '$'; // Add the literal '$' to the buffer
				(*len)++;
				*i = j; // Move past the space
				continue; // Skip the rest of the loop and process the last quote
			}

			// Handle regular variable expansion
			while (input[j] && !ft_strchr(not_env, input[j])) // Find the end of the variable name
				j++;
			char *var_name = ft_substr(input, *i + 1, j - (*i + 1)); // Extract the variable name
			if (!var_name)
			{
				printf("Error: Failed to allocate memory for variable name\n");
				// msh->exit_code = "NON SO ANCORA"
				// needs to also stop the tokenization
				return;
			}
			char *expansion = find_envar(var_name, msh->ms_env);
			free(var_name); // Free the temporary variable name
			if (expansion)
			{
				int exp_len = strlen(expansion);
				if (*len + exp_len >= 1023) // Prevent buffer overflow
				{
					printf("Error: Buffer overflow during variable expansion\n");
					free(expansion);
					return;
				}
				for (int k = 0; k < exp_len; k++) // Copies the expansion into the buffer
				{
					buff[*len] = expansion[k];
					(*len)++;
				}
				free(expansion); // Frees the copied expansion
			}
			*i = j - 1; // Move *i to the last character of the variable name
		}
		else if (input[*i] != quote) // Copy other characters except for quotes
		{
			if (*len >= 1023) // Prevent buffer overflow
			{
				printf("Error: Buffer overflow in collect_str\n");
				// error code and stop
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











bool invalid_char(char *input, int i, t_tokens *tokens)
{
	char *invalid;				// seen outside string also && $(..)
	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
	int j;

	invalid = ";#&,`*~\\";  // seen outside string also && $(..)
	bounds = "|>< "; // characters that flag minishell we are starting a new token, unless these characters are inside " or '
	j = i;

	while(ft_strchr(invalid, input[j]))
	{
		j++;
		if(input[j] == '\0' || ft_strchr(bounds, input[j])) // problem when followed by other invalid symbls
		{
			printf("Minishell: invalid token %c at input[%d]\n", input[i], i); // why wrong input
			free_tokens(tokens);
			return(false);
		}
		if(!ft_strchr(invalid, input[j]))
			break;
	}
	return(true);
}


t_tokens *parse_string(char *input, int *i, t_msh *msh, t_tokens *tokens)
{
	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
	char *quotes;
	char buff[1024] = {0};
	int len = 0;
	bounds = " \t\n|><"; // Add more boundaries if needed
	quotes = "\'\"";

	while (!ft_strchr(bounds, input[*i]) && input[*i] != '\0')
	{
		// Handles quoted tokens - OK should return err too
		if (ft_strchr(quotes, input[*i]))
		{
			int last_quote = 0;
			if (!quote_closed(i, input, input[*i], &last_quote))
			{
				// printf("Minishell: %c at input[%d] had no closure\n", input[*i], *i);
				msh->exit_code = 2;
				return (NULL);
			}
			collect_str(i, input, input[*i], &len, buff, &last_quote, msh);
			if(input[*i] == ' ' || input[*i] == '\0' || ft_strchr(bounds, input[*i]))
			{
				if (len > 0)
				{
					append_token(&tokens, create_token(buff, ARG));
				}
			}
		}
		// Handle environment variable expansion
		else if (input[*i] == '$')
		{
			char exp_name[1024] = {0};
			int exp_len = 0;
			int j = *i + 1;
			char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";

			if (input[j] == '?') { // Special case for $?
				append_token(&tokens, create_token(ft_itoa(msh->exit_code), ARG));
				*i = j + 1;
				continue;
			}

			while (input[j] && !ft_strchr(not_env, input[j])) {
				exp_name[exp_len++] = input[j++];
			}
			exp_name[exp_len] = '\0';

			if (exp_len == 0) { // No valid environment variable
				append_token(&tokens, create_token("$", ARG));
				(*i)++;
				continue;
			}

			char *expansion = find_envar(exp_name, msh->ms_env);
			if (expansion) {
				append_token(&tokens, create_token(expansion, ARG));
				free(expansion);
			}
			*i = j;
		}
		// Handle unquoted, normal tokens
		else {
			buff[len++] = input[*i];
			(*i)++;
			if (input[*i] == ' ' || input[*i] == '\0' || ft_strchr(bounds, input[*i])) {
				buff[len] = '\0';
				if (len > 0) {
					append_token(&tokens, create_token(buff, ARG));
				}
			}
		}
	}
	return tokens;
}

bool valid_bound(char *input, int *i, t_tokens **tokens)
{
	int k;

	k = *i +1;
	if (input[*i] == '|')
	{
		if (input[k] == '|')
		{
			printf("Minishell: error || operator are just for bonus\n");
			return false; // Invalid operator
		}
		else
			append_token(tokens, create_token("|", PIPE));
	}
	else if (input[*i] == '>')
	{ // Handle > and >>
		if (input[k] != '\0' && input[k] == '>')
		{
			append_token(tokens, create_token(">>", APPEND));
			(*i)++;
		}
		else
			append_token(tokens, create_token(">", REDIR_OUT));
	}
	else if (input[*i] == '<')
	{
		if (input[k] != '\0' && input[k] == '<') {
			append_token(tokens, create_token("<<", HEREDOC));
			(*i)++;
		}
		else
			append_token(tokens, create_token("<", REDIR_IN));
	}

	return true; // Boundary was handled successfully
}

t_tokens *return_tokens(char *input, t_msh *msh)
{
	int i;
	t_tokens *tokens;

	i = 0;
	tokens = NULL;
	msh->exit_code = 0; // neeed to define exit code every time to avoid prev codes being permanent

	while (input[i] != '\0')
	{
		if(!invalid_char(input, i, tokens)) //should we actually do this or just avoid and print?
		{
			// unsure if update exit code as it's not really an error but we don't need to do this
			free_tokens(tokens);
			return(NULL);
		}
		tokens = parse_string(input, &i, msh, tokens); // Call the parsing function
		// if(error)
		if(msh->exit_code != 0)
		{
			free_tokens(tokens);
			return(NULL);
		}
		if (!valid_bound(input, &i, &tokens))
		{
			free_tokens(tokens);
			return NULL;
		}
		if(input[i] != '\0')
			i++;
	}
	return(tokens); // <- return error as this
}
