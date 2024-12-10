/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:18 by jslusark          #+#    #+#             */
/*   Updated: 2024/12/10 15:46:04 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != c)
	{
		// write(1, &c,1);
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
/* #include<stdio.h>
int	main(void)
{
	// returns a pointer to the first occurence of c
	printf("%s\n", ft_strchr("teste",'e'));
	printf("%s\n", ft_strchr("teste", '\0'));
	printf("%s\n", ft_strchr("pepe y cparlos",'c'));
} */
