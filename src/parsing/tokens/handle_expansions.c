/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:40:17 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/26 20:16:52 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// ONLY THINGS TO HANDLE IS $"USER" -> spaceUSER because of invalid_exp part

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

void	expand_to_buff(char *expansion, char *buff, int *len, t_msh *msh)
{
	if (expansion)
	{
		int exp_len;
		int i;
		exp_len = strlen(expansion);
		if (*len + exp_len >= 1023) // Prevent buffer overflow
		{
			printf("Error: Buffer overflow during variable expansion\n");
			msh->exit_code = 2;
			free(expansion);
			return;
		}
		i = 0;
		while (i < exp_len)
		{
			buff[*len] = expansion[i];
			(*len)++;
			i++;
		}
		free(expansion);
	}
}

void handle_variable_expansion(char *input, int *i, char *buff, int *len, t_msh *msh)
{
	int end;
	char *var_name; // Extract the variable name
	char *expansion; // Extract the variable name


	end = *i;
	while (input[end] && !ft_strchr(EXP_LIMIT, input[end]))
		end++;
	var_name = ft_substr(input, *i, end - (*i));
	if (!var_name)
	{
		printf("Error: Failed to allocate memory for variable name\n");
		msh->exit_code = 2;
		return;
	}
	expansion = find_envar(var_name, msh->ms_env);
	free(var_name);
	expand_to_buff(expansion, buff, len, msh);
	*i = end; // Move *i to the last character of the variable name
}

void handle_invalid_expansion(char *buff, int *len)
{
	buff[*len] = '$'; // Adds just $
	(*len)++;
}
void handle_exit_expansion(int *i, char *buff, int *len, t_msh *msh)
{
	int exp_len;
	char *exp_exit;
	int j;

	exp_exit = ft_itoa(msh->exit_code); // Convert exit code to string
	exp_len = strlen(exp_exit);
	(*i)++; // skips ? as it's expanded
	j = 0;
	if (*len + exp_len >= 1023) // Prevent buffer overflow
	{
		printf("Error: Buffer overflow during $? expansion\n");
		msh->exit_code = 2;
		free(exp_exit);
		return;
	}
	while (j < exp_len)
	{
		buff[*len] = exp_exit[j];
		(*len)++;
		j++;
	}
	// // printf("\t- BUFF:%s\n", buff);
	free(exp_exit); // Free the dynamically allocated exit code string
}

void collect_expansion(char *input, int *i, char *buff, t_msh *msh)
{
	int len;

	len = ft_strlen(buff);
	(*i)++; // skips $, lands on next char to see exp

	if (ft_strchr(EXP_LIMIT, input[*i])) // if after $ there is not env
		handle_invalid_expansion(buff, &len);
	else if (input[*i] == '?')
		handle_exit_expansion(i, buff, &len, msh);
	else
		handle_variable_expansion(input, i, buff, &len, msh);
	(*i)--; // To avoid skipping the last character in the main loop
}
