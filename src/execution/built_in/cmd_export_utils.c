/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:13:01 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/10 17:16:59 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

void print_exported(char **env)
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
				if (sorted_env[i][j + 1] == '\0') // in the case of (export x=) we need this to avoid saving it as export x=" <- it needs both quotes
					ft_putchar_fd('"', 1);             // Add a quote at the end of the value
			}
			else if (sorted_env[i][j + 1] == '\0' && inside_value)
			{
				ft_putchar_fd(sorted_env[i][j], 1); // Write the last character of the value
				ft_putchar_fd('"', 1);             // Add a quote at the end of the value
			}
			else
				ft_putchar_fd(sorted_env[i][j], 1); // Write the character as is - useful for (export z)
			j++;
		}
		ft_putchar_fd('\n', 1); // Add a newline
		i++;
	}
	free(sorted_env); // only the pointer array needs to be freed as we did just a shallow copy of the envs for the sorting
}