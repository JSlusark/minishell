/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:43:06 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 14:35:44 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool check_empty_string(int *i, char *input, int *len, char *buff, int *last_quote)
{
	printf("start i: %d last_quote_pos: %d\n", *i, *last_quote); // ""
	int prev_i = *i - 1; // character before the 1st quote
	int next_i = *last_quote + 1; // character after the last quote
	printf("prev_i: %d next_i: %d len: %d\n", prev_i, next_i, *len);

	if(*i + 1 == *last_quote)
	{
		if((prev_i  < 0 || input[prev_i] == ' ') && (input[next_i] == ' ' || input[next_i] == '\0' ))
			{
				printf(COLOR_RED"HIT\n"COLOR_RESET);
				*i = next_i;
				buff[*len] = ' ';
				(*len)++;
				return(true); // stops and appends a token with space (cases where "" is empty and delimited by spaces or start/end string delimiters)
			}
	}
	return(false);
}

void collect_str(int *i, char *input, char quote, int *len, char *buff, int *last_quote, t_msh *msh)
{

	if(check_empty_string(i, input, len, buff, last_quote)) // if empty string is delimited by spaces or delimiters returns
		return;

	// if(*i + 1 == *last_quote)
	// {
	// 	//if i -1 is  - 1 || if input[i - 1] == space
	// 	// &&
	// 	// if input[i + 1] == space || input[i + 1] == '\0'
	// 	// then we have an empty string of 1 space
	// 	if( (*i - 1) == -1 || input[*i - 1] == ' ')
	// 	{
	// 		if(input[*i + 1] == ' ' || input[*i + 1] == '\0')
	// 		{
	// 			buff[*len] = ' ';
	// 			(*len)++;
	// 			(*i)++;
	// 			return;
	// 		}
	// 	}
	// }


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

t_tokens *tokenize(char *input, int *i, t_msh *msh, t_tokens *tokens) // everything should be freed here only
{
	while(input[*i] == ' ') // added to solve some "" edge cases
	{
		printf("SKIPPED SPACE AT input[%d]: %c\n", *i, input[*i]);
		(*i)++;
	}
	if (!invalid_char(input, *i, tokens)) {
		free_tokens(tokens);
		return NULL;
	}
	tokens = parse_string(input, i, msh, tokens);
	if (msh->exit_code != 0)
	{
		free_tokens(tokens);
		return NULL;
	}
	if (!valid_bound(input, i, &tokens)) {
		free_tokens(tokens);
		return NULL;
	}
	return tokens;
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
		tokens = tokenize(input, &i, msh, tokens);
		if (!tokens)
			return NULL; // Exit on error
		if (input[i] != '\0')
			i++;
	}
	return(tokens); // <- return error as this
}
