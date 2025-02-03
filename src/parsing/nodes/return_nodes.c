/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslusark <jslusark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:37 by jslusark          #+#    #+#             */
/*   Updated: 2025/02/03 13:22:58 by jslusark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	parse_rest(t_tokens **token, t_node_list *new_node,
					int token_n, t_flags **p)
{
	if ((*p)->find_cmd)
	{
		(void)token_n; // remove
		if (!alloc_cmd(new_node, *token, p))
			return (false);
		(*p)->find_cmd = false;
	}
	else
	{
		if ((*p)->found_echo && !new_node->cmd->args
			&& new_node->cmd->option_n == false)
			add_option_n(token, new_node);
		else
		{
			if (!add_argument(&(new_node->cmd->args), (*token)->value))
				return (false);
		}
	}
	return (true);
}

bool	parse_token(t_flags *p, t_tokens **token,
					t_node_list **head, t_node_list **new_node)
{
	if ((*token)->type == PIPE)
		end_new_node(&(p->start_node), head, *new_node, *token, p->token_n);
	else
	{
		p->pipestart = false;
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
			|| (*token)->type == APPEND || (*token)->type == HEREDOC)
		{
			if (!parse_redir(token, *new_node, &(p->redir_i)))
				return (false);
			p->token_n++;
		}
		else
			if (!parse_rest(token, *new_node, p->token_n, &p))
				return (false);
	}
	*token = (*token)->next;
	return (true);
}

t_flags	assign_data(void)
{
	t_flags	param;

	param.node_n = 1;
	param.redir_i = 0;
	param.token_n = 1;
	param.start_node = true;
	param.find_cmd = true;
	param.pipestart = true;
	param.found_echo = false;
	return (param);
}

t_node_list	*return_nodes(t_tokens *token, t_msh *msh)
{
	t_flags			p;
	t_node_list		*head;
	t_node_list		*new_node;

	p = assign_data();
	head = NULL;
	while (token != NULL)
	{
		if (pipe_error(token, p.pipestart, head, new_node))
		{
			msh->exit_code = 2;
			return (NULL);
		}
		if (p.start_node == true)
		{
			new_node = init_new_node(p.node_n, &p.start_node, msh);
			if (!new_node)
				return (NULL);
			p.find_cmd = true;
			p.found_echo = false;
			p.redir_i = 0;
			p.node_n++;
		}
		if (!parse_token(&p, &token, &head, &new_node))
		{
			free_node_list(head);
			free_node_list(new_node);
			return (NULL);
		}
		p.token_n++;
	}
	if (new_node)
		append_node(&head, new_node);
	return (head);
}
