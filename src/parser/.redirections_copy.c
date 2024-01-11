/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:35:09 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/11 11:51:40 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	link_redirections(t_token **tokens, t_parser_redir_utils *u, int i)
{
	u->head = NULL;
	u->prev_redir = NULL;
	while (--i && tokens[i]->type != PIPE)
	{
		if (token_is_redirection(tokens[i]))
		{
			if (u->prev_redir)
			{
				tokens[i]->left = u->prev_redir;
				u->prev_redir->parent = tokens[i];
			}
			u->prev_redir = tokens[i];
			u->head = tokens[i];
		}
	}
	if (tokens[i] && tokens[i]->type == PIPE)
		u->pipe = tokens[i];
	return (i);
}

t_token	*parse_redirections(t_token **tokens)
{
	t_parser_redir_utils	u;
	int	i;

	u.pipe = NULL;
	i = -1;
	while (tokens[++i]);
	i = link_redirections(tokens, &u, i);
	while (i > 0)
	{
		if (u.head && u.pipe)
		{
			u.pipe->right = u.head;
			u.head->parent = u.pipe;
		}
		i = link_redirections(tokens, &u, i);
	}
	if (u.pipe && u.head)
	{
		u.pipe->left = u.head;
		u.head->parent = u.pipe;
		return NULL;
	}
	else 
		return (u.head);
}


