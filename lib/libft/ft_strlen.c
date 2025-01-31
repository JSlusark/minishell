/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:27 by jslusark          #+#    #+#             */
/*   Updated: 2025/01/31 22:21:20 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	// if (!s)
	// 	return (0); // <---- JESS: Ste perche' lo hai messo? len 0 dovrebbe tornare gia'
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
/* #include <stdio.h>
int	main(void)
{
	printf("%zu\n", ft_strlen("123456")); //6
	printf("%zu\n", ft_strlen("123")); //3
	printf("%zu\n", ft_strlen("Hello World")); //11
	printf("%zu\n", ft_strlen("/&90hsb\'s^-")); //11
	printf("%zu\n", ft_strlen("X")); //1
} //ok */
