/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:29:23 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/19 15:41:50 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	token_is_redirection(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_HEREDOC || token->type == REDIR_APPEND);
}

t_token	*parser(t_token **tokens)
{
	t_token *ast_head;
	t_token	*ret1;
	t_token	*ret2;
	t_token	*ret3;
	t_token	*ret4;

	ast_head = NULL;
	ret1 = parse_pipes(tokens);
	ret2 = parse_redirections(tokens);
	ret3 = parse_commands(tokens);
	ret4 = parse_arguments(tokens);
	if (ret1)
		ast_head = ret1;
	else if (ret2)
		ast_head = ret2;
	else if (ret3)
		ast_head = ret3;
	else if (ret4)
		ast_head = ret4;
	return (ast_head);
}
