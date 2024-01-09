/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:15:56 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/09 11:34:25 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	init_tokenizer_utils(t_tokenizer_utils *u, const char *input)
{
	u->size = 0;
	u->capacity = 10;
	u->start = 0;
	u->current = 0;
	u->quoting_status = UNQUOTED;
	u->tokens = (t_token **)malloc(u->capacity * sizeof(t_token*));
	if (!u->tokens)
		return (0);
	return (1);
}

t_token	*create_token(t_tokenizer_utils *u, char *token_value)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->quoting_status = u->quoting_status;
	new_token->type = UNDEFINED;
	new_token->value = token_value;
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->parent = NULL;
	new_token->input = 0;
	new_token->output = 1;
	return new_token;
}

t_token	**add_token(t_tokenizer_utils *u, char *token_value)
{
	int new_capacity;
	int	i;
	t_token	**new_tokens;

	if (u->size + 1 >= u->capacity)
	{
		new_capacity = u->capacity * 2;
		new_tokens = (t_token **)malloc(new_capacity * sizeof(t_token *));
		if (!new_tokens)
			return (NULL);
		i = -1;
		while (++i < u->size)
			new_tokens[i] = u->tokens[i];
		free(u->tokens);
		u->tokens = new_tokens;
		u->capacity = new_capacity;
	}
	u->tokens[u->size] = create_token(u, token_value);
	(u->size)++;
	u->tokens[u->size] = NULL;
	return (u->tokens);
}

t_token **tokenize(const char *input)
{
	t_tokenizer_utils u;

	if (!init_tokenizer_utils(&u, input))
		return NULL;
	while (input[u.current])
	{
		u.c = input[u.current];
		if ((u.c == '|' || u.c == '<' ||u.c == '>') && u.quoting_status == UNQUOTED)
			handle_special_char(input, &u);
		else if ((u.c == ' ' || u.c == '\n' || u.c == '\t') && u.quoting_status == UNQUOTED) 
			handle_whitespace(input, &u);
		else if (u.c == '\'')
			handle_single_quote(input, &u);
		else if (u.c == '\"')
			handle_double_quote(input, &u);
		u.current++;
	}
	if (u.start != u.current)
		handle_last_token(input, &u);
    return (u.tokens);
}

/* int main() { */
/*     const char *input = "echo 'Hello 'World>> 'output.txt"; */
/*     t_token **tokens = tokenize(input); */

/*     int i = 0; */
/*     while (tokens[i] != NULL) { */
/*         printf("Token: %s\n", tokens[i]->value); */
/*         free(tokens[i]->value); */
/*         free(tokens[i]); */
/*         i++; */
/*     } */
/*     free(tokens); */
/*     return 0; */
/* } */

