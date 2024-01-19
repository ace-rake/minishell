/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:34:57 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/19 15:34:24 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	link_command_arguments(t_token **tokens, int i)
{
	while (tokens[i + 1] && tokens[i + 1]->type == ARGUMENT)
	{
		tokens[i]->right = tokens[i + 1];
		tokens[i + 1]->parent = tokens[i];
		i++;
	}
}

t_token	*parse_arguments(t_token **tokens)
{
	int	i;

	if (tokens[0] && !tokens[1] && tokens[0]->type == ARGUMENT)
		return (tokens[0]);
	i = -1;	
	while (tokens[++i])
	{
		if (tokens[i]->type == COMMAND)
			link_command_arguments(tokens, i);
		else if (token_is_redirection(tokens[i]) && tokens[i + 1] && tokens[i + 1]->type == ARGUMENT)
		{
			tokens[i]->right = tokens[i + 1];
			tokens[i + 1]->parent = tokens[i];
		}
	}
	return (NULL);
}
