/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:12 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/20 13:36:10 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	token_is_redirection(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_HEREDOC || token->type == REDIR_APPEND);
}

static char	*check_syntax_errors(t_token **tokens)
{
	int		i;
	bool	pipe_ok;

	i = -1;
	pipe_ok = false;
	while (tokens[++i])
	{
		if (tokens[i]->type == COMMAND)
			pipe_ok = true;
		else if (tokens[i]->type == PIPE)
		{
			if (!pipe_ok)
				return ("|");
			pipe_ok = false;
		}
		else if (token_is_redirection(tokens[i]) && (!tokens[i + 1] || (tokens[i
						+ 1] && tokens[i + 1]->type != ARGUMENT)))
			return (tokens[i]->value);
	}
	if (!pipe_ok)
		return ("|");
	return (NULL);
}

bool	syntax_ok(t_token **tokens)
{
	char	*error_string;

	error_string = check_syntax_errors(tokens);
	if (error_string)
	{
		printf("minishell: syntax error near unexpected token `%s\'",
				error_string);
		return (false);
	}
	return (true);
}
