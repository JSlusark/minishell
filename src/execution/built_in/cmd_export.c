/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:02:57 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/28 17:28:11 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	notes:
	1. variable expansion does not print delimited with "" as in bash
	2. minishell shows a longer list of env_vars
	3.LS_COLORS does not show in bash export or env while it does in our minishell
 */

#include "../../../include/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



// _____________________PRINT_ENVARS_________________________
// Swap two strings in the array
void swap_strings(char **a, char **b)
{
	char *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// Sort environment variables alphabetically by name
void sort_env_vars(char **env)
{
	int i;
	int j;
	int count;
	char *var_a;
	char *var_b;
	int len_a;
	int len_b;

	i = 0;
	j = 0;
	count = 0;

	// Count the number of environment variables
	while (env[count] != NULL)
		count++;

	// Bubble sort implementation
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			var_a = env[j];
			var_b = env[j + 1];
			len_a = 0;
			len_b = 0;

			// Find the lengths of names (up to `=`)
			while (var_a[len_a] != '\0' && var_a[len_a] != '=')
				len_a++;
			while (var_b[len_b] != '\0' && var_b[len_b] != '=')
				len_b++;

			// Compare names and swap if needed
			if (strncmp(var_a, var_b, len_a < len_b ? len_a : len_b) > 0)
				swap_strings(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

void print_env_vars(char **env)
{
	int i;
	int j;
	bool inside_value;
	char **sorted_env;

	i = 0;
	j = 0;
	inside_value = false;

	// Count environment variables
	int count = 0;
	while (env[count] != NULL)
		count++;

	// Create a sorted copy of the environment variables
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return;

	while (i < count)
	{
		sorted_env[i] = env[i];
		i++;
	}
	sorted_env[count] = NULL;

	// Sort the copied environment variables
	sort_env_vars(sorted_env);

	// Print the sorted environment variables
	i = 0;
	while (sorted_env[i] != NULL)
	{
		write(1, "export ", 7); // Write "export " at the start

		j = 0;
		inside_value = 0;
		while (sorted_env[i][j] != '\0') // NEED TO FIX FOR "export ZUZU=" needs to "export ZUZU="" " - just write as export ZUZU="
		{
			if (sorted_env[i][j] == '=' && !inside_value)
			{
				ft_putchar_fd(sorted_env[i][j], 1); // Write '='
				ft_putchar_fd('"', 1);             // Add a quote after '=' only if env is not null (for example export ZO=)
				inside_value = true;
			}
			else if (sorted_env[i][j + 1] == '\0' && inside_value)
			{
				ft_putchar_fd(sorted_env[i][j], 1); // Write the last character of the value
				ft_putchar_fd('"', 1);             // Add a quote at the end of the value
			}
			else
			{
				ft_putchar_fd(sorted_env[i][j], 1); // Write the character as is
			}
			j++;
		}
		ft_putchar_fd('\n', 1); // Add a newline
		i++;
	}

	// Free the sorted environment variables
	free(sorted_env);
}
///__________________________________________________________






// Main exec_export function
void exec_export(char **av, t_node_list *node)
{
	if (av == NULL)
	{
		// Print sorted environment variables
		print_env_vars(node->msh->ms_env);
		node->msh->exit_code = 0;
		// return;
	}
	else if(av[1]) // if we have more args in export we have diff edge cases
	{
			int j;
			j = 0;
			bool op_sign;

			op_sign = false;
			while (av[j]) // 1 - if we find the op sign in the other args
			{
				if (ft_strchr(av[j], '=')) // error in cases like "export sjsj =dd =ss dd" BUT NOT ERROR in "export x=1 y=2" or "export ci= ca=" where we create 2 exp
				{
					printf("export: `%s': not a valid identifier\n", av[j]);
					op_sign= true;
					break;
				}
				j++;
			}
			if(!op_sign) // cases like "export hello ciao" will create 2 envar with null assignation
			{
				j = 0;
				while (av[j])
				{
					ms_set_env(node->msh, av[j]);
					j++;
				}
			}
		}
		else
			ms_set_env(node->msh, av[0]); // needs to change with if i have consecutive = i should skip it (export STR==hi)
}
