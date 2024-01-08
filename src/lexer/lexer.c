/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:05:58 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/08 10:16:00 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_token_type(t_token *token, int *is_command)
{
	if (ft_strcmp(token->value, "|") == 0)
	{
		token->type = PIPE;
		*is_command = 1;
	}
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = REDIR_OUT;
	else if (ft_strcmp(token->value, ">>") == 0)
		token->type = REDIR_APPEND;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = REDIR_IN;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = REDIR_HEREDOC;
	else
	{
		if (*is_command == 1)
			token->type = COMMAND;
		else
			token->type = ARGUMENT;
		*is_command = 0;
	}
}

void	lexer(t_token **tokens)
{
	int		is_command;
	int		i;

	is_command = 1;
	i = -1;
	while (tokens[++i] != NULL)
		set_token_type(tokens[i], &is_command);
}





#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *test_str = "echo hello > output.txt | cat";

    t_token **tokens = tokenize(test_str);
    if (tokens == NULL) {
        fprintf(stderr, "Tokenization failed.\n");
        return 1;
    }

    lexer(tokens);

    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token: %s, Type: %d\n", tokens[i]->value, tokens[i]->type);
        free(tokens[i]->value);
        free(tokens[i]);
    }
    free(tokens);

    return 0;
}

