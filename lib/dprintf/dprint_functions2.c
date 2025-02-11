/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:05:30 by stdi-pum          #+#    #+#             */
/*   Updated: 2025/02/11 13:38:22 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprint_number(int n, int fd, int *count)
{
	char	*str;

	str = ft_itoa(n);
	if (!(str))
		return (-1);
	ft_dprint_string(str, fd, count);
	free(str);
	return (*count);
}

int	ft_dprint_unsigned(unsigned int n, int fd, int *count)
{
	if (n >= 10)
		ft_dprint_unsigned(n / 10, fd, count);
	ft_dprint_char(n % 10 + '0', fd, count);
	return (*count);
}

int	ft_dprint_pointer(void *ptr, int fd, int *count)
{
	unsigned long	ptr_address;

	if (!ptr)
		return (ft_dprint_string("(nil)", fd, count));
	ft_dprint_string("0x", fd, count);
	ptr_address = (unsigned long)ptr;
	ft_dprint_hexa(ptr_address, 'x', fd, count);
	return (*count);
}
