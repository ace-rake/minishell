/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:05:58 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/24 10:42:04 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	mark_metacharacters(t_token **tokens)
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

static void	set_flags(t_token *token, int *flag_first, int *flag_redirection)
{
	if (token->type == PIPE)
	{
		*flag_first = 1;
		*flag_redirection = 0;
	}
	else
		*flag_redirection = 1;
}

static void	mark_commands_and_arguments(t_token **tokens)
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

t_token	**lexer(t_token **tokens)
{
	mark_metacharacters(tokens);
	mark_commands_and_arguments(tokens);
	if  (syntax_ok(tokens))
		return (tokens);
	else
		return (NULL);
}

/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include "tokenizer.h" */

/* int	main(int argc, char **argv) */
/* { */
/* 	const char	*test_str; */
/* 	t_token		**tokens; */

/* 	if (argc != 2) */
/* 		return (1); */
/* 	test_str = argv[1]; */
/* 	tokens = tokenizer(test_str); */
/* 	if (tokens == NULL) */
/* 	{ */
/* 		fprintf(stderr, "Tokenization failed.\n"); */
/* 		return (1); */
/* 	} */
/* 	if (!lexer(tokens)) */
/* 		return (1); */
/* 	for (int i = 0; tokens[i] != NULL; i++) */
/* 	{ */
/* 		printf("Token: %s, Type: %d\n", tokens[i]->value, tokens[i]->type); */
/* 		free(tokens[i]->value); */
/* 		free(tokens[i]); */
/* 	} */
/* 	free(tokens); */
/* 	return (0); */
/* } */
