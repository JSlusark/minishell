/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moke_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:09:51 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/10 16:10:03 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token mock_tokens_1[] = {
	{COMMAND, {"echo"}},            // echo
	{STRING_LITERAL, {"hello"}},    // hello
};

t_token mock_tokens_2[] = {
	{COMMAND, {"echo"}},            // echo
	{STRING_LITERAL, {"hello"}},    // hello
	{PIPE, {"|"}},                  // |
	{COMMAND, {"cat"}},             // cat
};
