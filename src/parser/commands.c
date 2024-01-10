/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:35:01 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/10 14:54:30 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	link_command(t_token **tokens, int i)
{
	t_token *command;

	command = tokens[i];
	if (i >= 2 && tokens[i - 1]->type == ARGUMENT && token_is_redirection(tokens[i - 2]))
	{
		command->parent = tokens[i - 2];
		tokens[i - 2]->left = command;
		return (NULL);
	}
	else
	{
		while (tokens[++i] && tokens[i]->type != PIPE && !token_is_redirection(tokens[i]));
		if (tokens[i] && (tokens[i]->type == PIPE || token_is_redirection(tokens[i])))
		{
			command->parent = tokens[i];
			tokens[i]->left = command;
			return (NULL);
		}
		//TODO:does not link in case of input with pipes, without redirections in last simple command
	}
	return (command);
}

t_token	*parse_commands(t_token **tokens)
{
	int	i;
	t_token *head;
	
	i = -1;
	while (token[++i])
		if (token[i]->type == COMMAND)
			head = link_command(tokens);
	return (head);
}

