/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:52:18 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/24 15:48:52 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	handle_special_char(const char *input, t_tokenizer_utils *u)
{
	char	next_char;

	if (u->start != u->current)
		if (add_token(u, ft_strndup(input + u->start, u->current - u->start)) == 1)
			return (1);
	next_char = input[u->current + 1];
	if ((u->c == '>' && next_char == '>') || (u->c == '<' && next_char == '<'))
	{
		if (add_token(u, ft_strndup(input + u->current, 2)) == 1)
			return (1);
		u->current++;
	}
	else
		if (add_token(u, ft_strndup(input + u->current, 1)) == 1)
			return (1);
	u->start = u->current + 1;
	return (0);
}

int	handle_whitespace(const char *input, t_tokenizer_utils *u)
{
	if (u->start != u->current)
		if (add_token(u, ft_strndup(input + u->start, u->current - u->start)) == 1)
			return (1);
	u->start = u->current + 1;
	return (0);
}

void	handle_single_quote(t_tokenizer_utils *u)
{
	if (u->quoting_status == SINGLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = SINGLE_QUOTED;
}

void	handle_double_quote(t_tokenizer_utils *u)
{
	if (u->quoting_status == DOUBLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = DOUBLE_QUOTED;
}

int	handle_last_token(const char *input, t_tokenizer_utils *u)
{
	char	*token_str;

	if (u->quoting_status == UNQUOTED)
	{
		if (add_token(u, ft_strndup(input + u->start, u->current - u->start)) == 1)
			return (1);
	}
	else
	{
		token_str = ft_strndup(input + u->start, u->current - u->start);
		if (u->quoting_status == SINGLE_QUOTED)
		{
			printf("> '\n");
			if (add_token(u, ft_strjoin(token_str, "\'")) == 1)
				return (1);
		}
		else if (u->quoting_status == DOUBLE_QUOTED)
		{
			printf("> \"\n");
			if (add_token(u, ft_strjoin(token_str, "\"")) == 1)
				return (1);
		}
		free(token_str);
	}
	return (0);
}
