/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:31 by jslusark          #+#    #+#             */
/*   Updated: 2024/11/13 15:57:29 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
// #include "minishell.h"

// The scanning function (which we can also call tokenizer), should give us a linked list of tockens as the mock struct below
typedef struct s_mock
{
    int mock_type;         // Type of the token, e.g., COMMAND, STRING_LITERAL, etc.
    char *mock_value;      // Value of the token, e.g., "echo", "hello"
    struct s_mock *next_token; // Pointer to the next token in the linked list
}			t_mock;

typedef struct s_node // nodes are commands (builtins or the ones we repilcate) followed by args. Args can be of type str, redir, or flags)
{
	t_mock	token; // we get value and type of token (if first token is not a command what do we do?)
	// we might need to have some redirection checks and structs here
	t_mock	*next_token; // next tokens will be args, if there is no next token, need to check what happens in bash
	// if next token after 1st command is another command it will be treated as a string (type echo cat in terminal and see)
}		t_node; // we create these until we encounter a pipe or next mock token is null

typedef	struct  s_node_table //if next token is PIPE we create this
{
	t_node  cmd;
	int pipe; // true or false
	struct s_node_table *next_cmds; // Pointer to the next command in the pipeline (use struct keyword for recursive structs)
	//if pipe true and next_cmds is null it is error (we cannot END a command w)
	// if pipe true, and next_cmds->next is null it means we have just one command following the pipe and not more we need to consider after
}	t_node_table;

// IMPORTANT: THE AST IS NEEDED ONLY FOR THE BONUS BECAUSE && AND || OPERATORS ARE WHAT BUILD TREES, WHITHOUT THEM WE ONLY HAVE A SEQUENCE OF COMMAND TABLES
typedef	struct s_ast
{
	t_node_table	cmd_table; // the cmd table made of nodes and pipes
	t_token		table_conjunction; // the && and || operators
	t_node_table	next_cmd_table; // the next cmd table made of nodes and pipes
}	t_ast; // without bonus t_ast will only have cmd_table while the rest of teh data is empty


t_ast	*parse(t_mock *mock_token); // mock version
t_mock *create_mock_tokens(char *input);



// FINDING OUT NODES FROM ANOTHER PROJECT

//Sources:
//https://github.com/DimitriDaSilva/42_minishell/blob/master/src/parse/parse.c#L100
//https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/sh.c

// typedef struct s_redir // can we use this instead than t_list inside t_cmd?
// {
//   int type;
// //   struct cmd *cmd;
//   char *file;
//   char *efile;
//   int mode;
//   int fd;
// }	t_redir;

// typedef struct s_cmd // contains tokensare r
// {
// 	t_list	*tokens;
// 	t_redir	*redirections;
// }			t_cmd;

// typedef struct s_list
// {
// 	void		*data;
// 	t_list		*next;

// }			t_list;

// void add_to_list(t_redir redirection_list, ft_lstnew(redir));

#endif
