/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:24:44 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/31 11:32:09 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *parse_redirections(t_token **tokens)
{
	t_parser_utils_redir	u;
	int i;

	u.last_redirection = NULL;
	u.first_redirection = NULL;
	u.pipe = NULL;
	i = -1;
	while (tokens[++i])
	{
		if (token_is_redirection(tokens[i]))
		{
			if (u.last_redirection)
			{
				tokens[i]->parent = u.last_redirection;
				u.last_redirection->left = tokens[i];
			}
			else
				u.first_redirection = tokens[i];
			u.last_redirection = tokens[i];
		}
		else if (tokens[i]->type == PIPE)
		{
			if (u.pipe && u.first_redirection)
			{
				u.pipe->right = u.first_redirection;
				u.first_redirection->parent = u.pipe;
			}
			else if (!u.pipe && u.first_redirection)
			{
				u.pipe = tokens[i];
				u.pipe->left = u.first_redirection;
				u.first_redirection->parent = u.pipe;
			}
			u.pipe = tokens[i];
			u.last_redirection = NULL;
			u.first_redirection = NULL;
		}
	}
	if (u.first_redirection && u.pipe)
	{
		u.pipe->right = u.first_redirection;
		u.first_redirection->parent = u.pipe;
	}
	return (u.first_redirection);
}
