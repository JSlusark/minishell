/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:40:17 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 18:57:18 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *find_envar(char *var, char **env) // finds only the var, does not expand
{
	// printf("ENVAR NAME %s\n", var)
;	int i;
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

void collect_expansion(char *input, int *i, char *buff, t_msh *msh)
{
	char *not_env;
	int len;

	len = ft_strlen(buff);
	not_env = "!@#$%%^&*()-+=[]{}|\\:;'\"/<>,.`~ ";
	// printf("collect expansion called:\n");
	// printf("\t- char:%c\n\t- i:%d\n", input[*i], *i);
	(*i)++; // skips $, lands on next char to see exp
	// printf("\t- char:%c\n\t- i:%d\n", input[*i], *i);

	if (ft_strchr(not_env, input[*i])) // if after $ there is not env
	{
		// printf("HIT BOUND NO EXPANSION NEEDED\n");
		buff[len++] = '$'; // adds just $ and stays on the bound to process later in cond
		(*i)--; // to avoid skipping the last ch
		// printf("\t- BUFF:%s\n", buff);
		return;
	}
	else if (input[*i] == '?')
	{
		// printf("HIT EXIT, EXPANDING TO CODE\n");
		int j = 0; // Use a while loop instead of a for loo
		int exp_len;
		char *exp_exit;
		exp_exit = ft_itoa(msh->exit_code); // Convert exit code to string
		exp_len = strlen(exp_exit);
		(*i)++; // skips ? as it's expanded
		if (len + exp_len >= 1023) // Prevent buffer overflow
		{
			// printf("Error: Buffer overflow during $? expansion\n");
			free(exp_exit);
			return;
		}
		while (j < exp_len) // copies exit code to buff
		{
			buff[len] = exp_exit[j];
			(len)++;
			j++;
		}
		// printf("\t- BUFF:%s\n", buff);
		free(exp_exit); // Free the dynamically allocated exit code string
		(*i)--; // to avoid skipping the last ch
		return;
	}
	else
	{
		int end;
		end = *i;
		char *var_name; // Extract the variable name
		char *expansion; // Extract the variable name
		while (input[end] && !ft_strchr(not_env, input[end])) // OR INPUT[end] is not nulL!!!
			end++;
		var_name = ft_substr(input, *i, end - (*i)); // Extract the variable name $USER
		if (!var_name)
		{
			printf("Error: Failed to allocate memory for variable name\n");
			msh->exit_code = 2;
			return;
		}
		expansion = find_envar(var_name, msh->ms_env);
		free(var_name); // Free the temporary variable name
		if (expansion) // WHAT IF EX IS NOT EXISTIG
		{
			int exp_len = strlen(expansion);
			if (len + exp_len >= 1023) // Prevent buffer overflow
			{
				printf("Error: Buffer overflow during variable expansion\n");
				msh->exit_code = 2;
				free(expansion);
				return;
			}
			int k = 0; // start of expansion string
			while (k < exp_len) // Copies the expansion into the buffer
			{
				buff[len] = expansion[k];
				(len)++;
				k++;
			}
			free(expansion); // Frees the copied expansion
			// *i = end - 1 ; // Move *i to the last character of the variable name
		}
		else
		{
			buff[len] = ' ';
			// *i = end - 1 ; // Move *i to the last character of the variable name
		}
		*i = end - 1 ; // Move *i to the last character of the variable name
		// printf(COLOR_RED"char landed: %c\n"COLOR_RESET, input[*i]);
	}
}
