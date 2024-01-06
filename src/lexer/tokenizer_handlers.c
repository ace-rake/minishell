/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:14:54 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/06 12:24:57 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	handle_special_char(const char *input, t_tokenizer_utils *u)
{
	char next_char;
		
	if (u->start != u->current)
		add_token(u, ft_strndup(input + u->start, u->current - u->start));
	next_char = input[u->current + 1];
	if ((u->c == '>' && next_char == '>') || (u->c == '<' && next_char == '<'))
	{
		add_token(u, ft_strndup(input + u->current, 2));
		u->current++;
	}
	else
		add_token(u, ft_strndup(input + u->current, 1));
	u->start = u->current + 1;
}

void	handle_whitespace(const char *input, t_tokenizer_utils *u)
{
	if (u->start != u->current)
		add_token(u, ft_strndup(input + u->start, u->current - u->start));
	u->start = u->current + 1;
}

void	handle_single_quote(const char *input, t_tokenizer_utils *u)
{
	if (u->quoting_status == SINGLE_QUOTED)
	{
		if (u->current > u->start + 1)
			add_token(u, ft_strndup(input + u->start + 1, u->current - u->start - 1));
		u->start = u->current + 1;
		u->quoting_status = UNQUOTED;
	}
	else if (u->quoting_status == UNQUOTED)	
		u->quoting_status = SINGLE_QUOTED; 
}

void	handle_double_quote(const char *input, t_tokenizer_utils *u)
{
	if (u->quoting_status == DOUBLE_QUOTED)
	{
		if (u->current > u->start + 1)
			add_token(u, ft_strndup(input + u->start + 1, u->current - u->start - 1));
		u->start = u->current + 1;
		u->quoting_status = UNQUOTED;
	}
	else if (u->quoting_status == UNQUOTED)	
		u->quoting_status = DOUBLE_QUOTED; 
}

void	handle_last_token(const char *input, t_tokenizer_utils *u)
{
	if (u->quoting_status == UNQUOTED)
		add_token(u, ft_strndup(input + u->start, u->current - u->start));
	else
	{
		if (u->quoting_status == SINGLE_QUOTED)
			printf("> '\n");
		else if (u->quoting_status == DOUBLE_QUOTED)
			printf("> \"\n");
		add_token(u, ft_strndup(input + u->start + 1, u->current - u->start - 1));
	}
}

