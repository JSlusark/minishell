/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:24:54 by alramire          #+#    #+#             */
/*   Updated: 2024/11/05 17:54:51 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef char *char_itr;

// Are still characters left to consume?
int has_next(const char_itr itr)
{
	return( *itr != '\n' && *itr != '\0');
}

//look ahead at the next character of input withput consuming it
char peek(const char_itr itr)
{
	return(*itr);
}

//Consume the next character of input
char next(char_itr itr)
{
	char next;

	next = **itr;
}
