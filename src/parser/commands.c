/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:09:40 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/20 15:23:31 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *parse_commands(t_token **tokens)
{
	t_token	*command;
	t_token	*redirection;
	t_token	*pipe;
	int	i;

	command = NULL;
	redirection = NULL;
	pipe = NULL;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == COMMAND)
		{
			command = tokens[i];
			if (i >= 2 && tokens[i - 1]->type == ARGUMENT && token_is_redirection(tokens[i - 2]))
			{
				redirection = tokens[i];
				redirection->left = command;
				command->parent = redirection;
			}
			else
			{
				while (tokens[++i] && tokens[i]->type != PIPE)
				{
					if (token_is_redirection(tokens[i]) && !tokens[i]->left)
					{
						redirection = tokens[i];
						redirection->left = command;
						command->parent = redirection;
					}
				}
				if (tokens[i] && tokens[i]->type == PIPE)
				{
					if (redirection)
					{
						redirection = NULL;
						pipe = tokens[i];
					}
					else if (!pipe)
					{
						pipe = tokens[i];
						pipe->left = command;
						command->parent = tokens[i];
					}
					else if (pipe)
					{
						pipe->right = command;
						command->parent = tokens[i];
						pipe = tokens[i];
					}
				}
			}
		}
	}
	if (pipe && command && !command->parent)
	{
		pipe->right = command;
		command->parent = pipe;
	}
	return (command);
}
