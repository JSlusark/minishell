/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:26 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/24 14:10:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_tokens *parse_string(char *input, int *i, t_msh *msh, t_tokens *tokens)
{
	char *bounds;				// characters that flag minishell we are starting a new token, unless these characters are inside " or '
	char *quotes;
	char buff[1024];

	memset(buff, 0, sizeof(buff));
	int len = 0;
	bounds = " \t\n|><"; // Add more boundaries if needed
	quotes = "\'\"";

	while (!ft_strchr(bounds, input[*i]) && input[*i] != '\0')
	{
		// Handles quoted tokens - OK should return err too
		if (ft_strchr(quotes, input[*i]))
		{
			printf(COLOR_CYAN"PART OF QUOTE STRING - "COLOR_RESET);
			printf("input[%d]: %c\n", *i, input[*i]);
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
			printf(COLOR_BLUE"PART OF NO_Q STRING - "COLOR_RESET);
			printf("input[%d]: %c\n", *i, input[*i]);
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