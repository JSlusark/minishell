/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:07:07 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/14 13:19:45 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Creating a function that prints the created tokens, this might be an important
testing function to see how the tokenizer(lexing and scanning) is passing tokens to
the token list.

For instance if we write:
	Minishell> echo hello

	- token value: echo
	- token type : command

	- token value: hello
	- token type : string

The tokenizer also needs to handle special cases when creating tokens, if we type:

	Minishell> e"c"ho hello

	- token value: echo
	- token type : command

	- token value: hello
	- token type : string
 */