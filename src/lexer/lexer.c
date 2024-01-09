/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:05:58 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/09 11:36:17 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	mark_metacharacters(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (ft_strcmp(tokens[i]->value, "|") == 0)
			tokens[i]->type = PIPE;
		else if (ft_strcmp(tokens[i]->value, ">") == 0)
			tokens[i]->type = REDIR_OUT;
		else if (ft_strcmp(tokens[i]->value, ">>") == 0)
			tokens[i]->type = REDIR_APPEND;
		else if (ft_strcmp(tokens[i]->value, "<") == 0)
			tokens[i]->type = REDIR_IN;
		else if (ft_strcmp(tokens[i]->value, "<<") == 0)
			tokens[i]->type = REDIR_HEREDOC;
	}
}

void	set_flags(t_token *token, int *flag_first, int *flag_redirection)
{
		if (token->type == PIPE)
		{
			*flag_first = 1;
			*flag_redirection = 0;
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
			*flag_redirection = 1;
}

void	mark_commands_and_arguments(t_token **tokens)
{
	int	flag_first;
	int	flag_redirection;
	int	i;

	flag_first = 1;
	flag_redirection = 0;
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->type != UNDEFINED)
			set_flags(tokens[i], &flag_first, &flag_redirection);
		else
		{
			if (flag_first && !flag_redirection)
			{
				tokens[i]->type = COMMAND;
				flag_first = 0;
			}
			else
			{
				tokens[i]->type = ARGUMENT;
				flag_redirection = 0;
			}
		}
	}
}

void	lexer(t_token **tokens)
{
	mark_metacharacters(tokens);
	mark_commands_and_arguments(tokens);
}




#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *test_str = "> output.txt echo hello | cat";

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

