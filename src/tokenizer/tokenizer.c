/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:52:18 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/24 15:01:13 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	init_tokenizer_utils(t_tokenizer_utils *u)
{
	u->size = 0;
	u->new_capacity = 0;
	u->capacity = 10;
	u->start = 0;
	u->current = 0;
	u->quoting_status = UNQUOTED;
	u->new_tokens = NULL;
	u->tokens = (t_token **)malloc(u->capacity * sizeof(t_token *));
	if (!u->tokens)
		return (0);
	return (1);
}

t_token	*create_token(char *token_value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = UNDEFINED;
	new_token->value = token_value;
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->parent = NULL;
	new_token->input = 0;
	new_token->output = 1;
	return (new_token);
}

t_token	**add_token(t_tokenizer_utils *u, char *token_value)
{
	int		i;

	if (u->size + 1 >= u->capacity)
	{
		u->new_capacity = u->capacity * 2;
		u->new_tokens = (t_token **)malloc(u->new_capacity * sizeof(t_token *));
		if (!u->new_tokens)
			return (NULL);
		i = -1;
		while (++i < u->size)
			u->new_tokens[i] = u->tokens[i];
		free(u->tokens);
		u->tokens = u->new_tokens;
		u->capacity = u->new_capacity;
	}
	u->tokens[u->size] = create_token(token_value);
	(u->size)++;
	u->tokens[u->size] = NULL;
	return (u->tokens);
}

t_token	**tokenizer(const char *input)
{
	t_tokenizer_utils	u;

	if (!init_tokenizer_utils(&u))
		return (NULL);
	while (input[u.current])
	{
		u.c = input[u.current];
		if ((u.c == '|' || u.c == '<' || u.c == '>')
			&& u.quoting_status == UNQUOTED)
			handle_special_char(input, &u);
		else if ((u.c == ' ' || u.c == '\n' || u.c == '\t')
			&& u.quoting_status == UNQUOTED)
			handle_whitespace(input, &u);
		else if (u.c == '\'')
			handle_single_quote(&u);
		else if (u.c == '\"')
			handle_double_quote(&u);
		u.current++;
	}
	if (u.start != u.current)
		handle_last_token(input, &u);
	return (u.tokens);
}
