/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:29:23 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/10 11:01:47 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*parse_pipes(t_token **tokens)
{
	t_token *head;
	t_token	*prev_pipe;
	int		i;

	head = NULL;
	prev_pipe = NULL;
	i = 0;
	while (tokens[i++]);
	while (i--)
	{
		if (tokens[i]->type == PIPE)
		{
			if (head == NULL)
				head = tokens[i];
			else
			{
				tokens[i]->parent = prev_pipe;
				prev_pipe->left = tokens[i];
			}
			prev_pipe = tokens[i];
		}
	}
	return (head);
}

t_token	*parse_redirections(t_token **tokens, t_parser_redir_utils *u, int i)
{
	u->head = NULL;
	u->prev_redir = NULL;
	u->pipe = NULL;
	while (i-- && tokens[i]->type != PIPE)
	{
		if (tokens[i]->type == REDIR_IN || tokens[i]->type == REDIR_OUT
			|| tokens[i]->type == REDIR_HEREDOC || tokens[i]->type == REDIR_APPEND)
		{
			if (u->prev_redir)
			{
				tokens[i]->right = u->prev_redir;
				u->prev_redir->parent = tokens[i];
			}
			u->prev_redir = tokens[i];
			u->head = tokens[i];
		}
	}
	return (i);
}

t_token	*parse_redirections(t_token **tokens)
{
	t_parser_redir_utils	u;
	int	i;

	i = 0;
	while (tokens[i++]);
	while (i > 0)
	{
		i = parse_redirections(tokens, &u, i);
		u.pipe = tokens[i];
		u.pipe->right = u.head;
		u.head->parent = u.pipe;
	}
	if (u.pipe)
	{
		u.pipe->left = u.head;
		u.head->parent = u.pipe;
		return NULL
	}
	else 
		return (head);
}

t_token	*parse_commands(t_token **tokens)
{

}

t_token	*parser(t_token **tokens)
{
	t_token	*ast_head;

}
