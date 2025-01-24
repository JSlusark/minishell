
// bool check_empty_string(int *i, char *input, int *len, char *buff, int *last_quote)
// {
// 	printf("start i: %d last_quote_pos: %d\n", *i, *last_quote); // ""
// 	int prev_i = *i - 1; // character before the 1st quote
// 	int next_i = *last_quote + 1; // character after the last quote
// 	printf("prev_i: %d next_i: %d len: %d\n", prev_i, next_i, *len);

// 	if(*i + 1 == *last_quote)
// 	{
// 		if((prev_i  < 0 || input[prev_i] == ' ') && (input[next_i] == ' ' || input[next_i] == '\0' ))
// 			{
// 				printf(COLOR_RED"HIT\n"COLOR_RESET);
// 				*i = next_i;
// 				buff[*len] = ' ';
// 				(*len)++;
// 				return(true); // stops and appends a token with space (cases where "" is empty and delimited by spaces or start/end string delimiters)
// 			}
// 	}
// 	return(false);
// }

// void collect_str(int *i, char *input, char quote, int *len, char *buff, int *last_quote, t_msh *msh)
// {

// 	if(check_empty_string(i, input, len, buff, last_quote)) // if empty string is delimited by spaces or delimiters returns
// 		return;

// 	// if(*i + 1 == *last_quote)
// 	// {
// 	// 	//if i -1 is  - 1 || if input[i - 1] == space
// 	// 	// &&
// 	// 	// if input[i + 1] == space || input[i + 1] == '\0'
// 	// 	// then we have an empty string of 1 space
// 	// 	if( (*i - 1) == -1 || input[*i - 1] == ' ')
// 	// 	{
// 	// 		if(input[*i + 1] == ' ' || input[*i + 1] == '\0')
// 	// 		{
// 	// 			buff[*len] = ' ';
// 	// 			(*len)++;
// 	// 			(*i)++;
// 	// 			return;
// 	// 		}
// 	// 	}
// 	// }


// 	while (*i <= *last_quote) // Process characters within the quoted string
// 	{
// 		// Check for variable expansion inside double quotes
// 		if (input[*i] == '$' && quote == '"') // Expand variables only inside double quotes
// 		{
// 			char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ "; // Characters not valid in variable names
// 			int j = *i + 1; // Start after the '$'

// 			// Check for $ followed by ?
// 			if (input[j] == '?')
// 			{
// 				char *exit_code_str = ft_itoa(msh->exit_code); // Convert exit code to string
// 				int exp_len = strlen(exit_code_str);
// 				if (*len + exp_len >= 1023) // Prevent buffer overflow
// 				{
// 					printf("Error: Buffer overflow during $? expansion\n");
// 					free(exit_code_str);
// 					return;
// 				}
// 				for (int k = 0; k < exp_len; k++) // Append the exit code string to the buffer
// 				{
// 					buff[*len] = exit_code_str[k];
// 					(*len)++;
// 				}
// 				free(exit_code_str); // Free the dynamically allocated exit code string
// 				*i = j + 1; // input[*] is ? so move past by j++;
// 				continue; // Skip the rest of the loop
// 			}

// 			// IF SHOULD BE ANY INVALID IS GUESS (echo "$'US'ER" comes $'US'ER)
// 			// Check for $ followed by space (ex: "? ", "? hello") or " (ex" "?")
// 			if (input[j] == ' ' || ft_strchr(not_env, input[j])) // $ does not expand if followed by space or not_env
// 			{
// 				if (*len + 1 >= 1023) // Prevent buffer overflow
// 				{
// 					printf("Error: Buffer overflow during $ expansion\n");
// 					return;
// 				}
// 				buff[*len] = '$'; // Add the literal '$' to the buffer
// 				(*len)++;
// 				*i = j; // Move past the space
// 				continue; // Skip the rest of the loop and process the last quote
// 			}

// 			// Handle regular variable expansion
// 			while (input[j] && !ft_strchr(not_env, input[j])) // Find the end of the variable name
// 				j++;
// 			char *var_name = ft_substr(input, *i + 1, j - (*i + 1)); // Extract the variable name
// 			if (!var_name)
// 			{
// 				printf("Error: Failed to allocate memory for variable name\n");
// 				// msh->exit_code = "NON SO ANCORA"
// 				// needs to also stop the tokenization
// 				return;
// 			}
// 			char *expansion = find_envar(var_name, msh->ms_env);
// 			free(var_name); // Free the temporary variable name
// 			if (expansion)
// 			{
// 				int exp_len = strlen(expansion);
// 				if (*len + exp_len >= 1023) // Prevent buffer overflow
// 				{
// 					printf("Error: Buffer overflow during variable expansion\n");
// 					free(expansion);
// 					return;
// 				}
// 				for (int k = 0; k < exp_len; k++) // Copies the expansion into the buffer
// 				{
// 					buff[*len] = expansion[k];
// 					(*len)++;
// 				}
// 				free(expansion); // Frees the copied expansion
// 			}
// 			*i = j - 1; // Move *i to the last character of the variable name
// 		}
// 		else if (input[*i] != quote) // Copy other characters except for quotes
// 		{
// 			if (*len >= 1023) // Prevent buffer overflow
// 			{
// 				printf("Error: Buffer overflow in collect_str\n");
// 				// error code and stop
// 				return;
// 			}
// 			buff[*len] = input[*i];
// 			(*len)++;
// 		}
// 		(*i)++;
// 	}
// }




// t_tokens *parse_string(char *input, int *i, t_msh *msh, t_tokens *tokens)
// {
// 	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
// 	char *quotes;
// 	char buff[1024];

// 	memset(buff, 0, sizeof(buff));
// 	int len = 0;
// 	bounds = " \t\n|><"; // Add more boundaries if needed
// 	quotes = "\'\"";

// 	while (!ft_strchr(bounds, input[*i]) && input[*i] != '\0')
// 	{
// 		// Handles quoted tokens - OK should return err too
// 		if (ft_strchr(quotes, input[*i]))
// 		{
// 			printf(COLOR_CYAN"PART OF QUOTE STRING - "COLOR_RESET);
// 			printf("input[%d]: %c\n", *i, input[*i]);
// 			int last_quote = 0;
// 			if (!quote_closed(i, input, input[*i], &last_quote))
// 			{
// 				// printf("Minishell: %c at input[%d] had no closure\n", input[*i], *i);
// 				msh->exit_code = 2;
// 				return (NULL);
// 			}
// 			collect_str(i, input, input[*i], &len, buff, &last_quote, msh);
// 			if(input[*i] == ' ' || input[*i] == '\0' || ft_strchr(bounds, input[*i]))
// 			{
// 				if (len > 0)
// 				{
// 					append_token(&tokens, create_token(buff, ARG));
// 				}
// 			}
// 		}
// 		// Handle environment variable expansion
// 		else if (input[*i] == '$')
// 		{
// 			char exp_name[1024] = {0};
// 			int exp_len = 0;
// 			int j = *i + 1;
// 			char *not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>?,.`~ ";

// 			if (input[j] == '?') { // Special case for $?
// 				append_token(&tokens, create_token(ft_itoa(msh->exit_code), ARG));
// 				*i = j + 1;
// 				continue;
// 			}

// 			while (input[j] && !ft_strchr(not_env, input[j])) {
// 				exp_name[exp_len++] = input[j++];
// 			}
// 			exp_name[exp_len] = '\0';

// 			if (exp_len == 0) { // No valid environment variable
// 				append_token(&tokens, create_token("$", ARG));
// 				(*i)++;
// 				continue;
// 			}

// 			char *expansion = find_envar(exp_name, msh->ms_env);
// 			if (expansion) {
// 				append_token(&tokens, create_token(expansion, ARG));
// 				free(expansion);
// 			}
// 			*i = j;
// 		}
// 		// Handle unquoted, normal tokens
// 		else {
// 			printf(COLOR_BLUE"PART OF NO_Q STRING - "COLOR_RESET);
// 			printf("input[%d]: %c\n", *i, input[*i]);
// 			buff[len++] = input[*i];
// 			(*i)++;
// 			if (input[*i] == ' ' || input[*i] == '\0' || ft_strchr(bounds, input[*i])) {
// 				buff[len] = '\0';
// 				if (len > 0) {
// 					append_token(&tokens, create_token(buff, ARG));
// 				}
// 			}
// 		}
// 	}
// 	return tokens;
// }