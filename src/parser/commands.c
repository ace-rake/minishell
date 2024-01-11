/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:35:01 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/11 09:51:42 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*link_command1(t_token **tokens, int i)
{
	t_token *command;

	command = tokens[i];
	command->parent = tokens[i - 2];
	tokens[i - 2]->left = command;
	return (NULL);
}

static t_token *link_command2(t_token **tokens, int i)
{
	t_token *command;
	static t_token *last_pipe;

	command = tokens[i];
	/* last_pipe = NULL; */
	while (tokens[++i] && tokens[i]->type != PIPE && !token_is_redirection(tokens[i]));
	if (tokens[i] && (tokens[i]->type == PIPE || token_is_redirection(tokens[i])))
	{
		if (tokens[i]->type == PIPE)
			last_pipe = tokens[i];
		command->parent = tokens[i];
		tokens[i]->left = command;
		return (NULL);
	}
	else if (!tokens[i] && last_pipe != NULL)
	{
		command->parent = last_pipe;
		last_pipe->right = command;
		return (NULL);
	}
	else
		return (command);
}

t_token	*parse_commands(t_token **tokens)
{
	int	i;
	t_token *head;
	t_token *command;
	
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == COMMAND)
		{
			if (i >= 2 && tokens[i - 1]->type == ARGUMENT && token_is_redirection(tokens[i - 2]))
				head = link_command1(tokens, i);
			else
				head = link_command2(tokens, i);
		}
	}
	return (head);
}

