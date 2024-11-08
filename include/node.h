/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/08 16:18:55 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H


// taken from following step by step kris jordan's
// video, this needs a more specific approach based on our minishell requirements

typedef enum s_node_type
{
	CHARACTER,
	PAIR,
}	t_node_type;

typedef char	t_char_value;

typedef struct s_pair_value
{
	t_node	node_l;
	t_node	node_r;
}	t_pair_value;

typedef union s_node_value
{
	t_pair_value	pair;
	t_char_value	character;
}	t_node_value;

typedef struct s_node
{
	t_node_type				node_type;
	t_node_value			data;

}	t_node;

#endif
