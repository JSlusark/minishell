/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:41:56 by jadyar            #+#    #+#             */
/*   Updated: 2025/02/11 14:26:15 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_itoa(int n);
int		ft_dprintf(const char *format, ...);
int		ft_dprint_format(const char specifier, va_list ap, int fd, int *count);
int		ft_dprint_unsigned(unsigned int n, int fd, int *count);
int		ft_dprint_number(int n, int fd, int *count);
int		ft_dprint_hexa(unsigned long n, char specifier, int fd, int *count);
int		ft_dprint_string(char *str, int fd, int *count);
int		ft_dprint_char(char c, int fd, int *count);
int		ft_dprint_pointer(void *ptr, int fd, int *count);

#endif