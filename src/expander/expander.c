/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:03:07 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/30 10:40:21 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_expander_utils(t_expander_utils *u, t_env_list *env, int exit_status)
{
	u->quoting_status = UNQUOTED;
	u->env = env;
	u->exit_status = exit_status;
	u->original = NULL;
	u->result = NULL;
	u->variable = NULL;
	u->before = NULL;
	u->after = NULL;
	u->temp = NULL;
}

void	toggle_single_quote(t_expander_utils *u)
{
	if (u->quoting_status == SINGLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = SINGLE_QUOTED;
}

void	toggle_double_quote(t_expander_utils *u)
{
	if (u->quoting_status == DOUBLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = DOUBLE_QUOTED;
}

int	handle_dollar_sign(t_expander_utils *u)
{
	if (u->original[u->i + 1] && u->original[u->i + 1] == '?')
	{
		u->variable = ft_itoa(u->exit_status);
		u->before = ft_strndup(u->original, u->i);
		u->after = ft_strdup(u->original + u->i + 2);
		u->result = ft_strjoin(u->before, u->variable);
		u->temp = u->result;
		u->result = ft_strjoin(u->result, u->after);
		free(u->variable);
		free(u->before);
		free(u->after);
		free(u->temp);
		u->i += ft_strlen(u->variable);
	}
	else
	{
		//TODO: toggle variable expansions
	}
	return (1);
}

int	expand_variables(t_expander_utils *u)
{
	char	c;

	u->i = -1;
	while (u->original[++(u->i)])
	{
		c = u->original[u->i];
		if (c == '$' && (u->quoting_status == UNQUOTED || u->quoting_status == DOUBLE_QUOTED))
		{
			if (!handle_dollar_sign(u))
				return (0);
		}
		else if (c == '\'')
			toggle_single_quote(u);
		else if (c == '\"')
			toggle_double_quote(u);
	}


	return (1);
}

int	expander(t_token **tokens, t_env_list *env, int exit_status)
{
	t_expander_utils	u;
	int		i;

	init_expander_utils(&u, env, exit_status);
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == ARGUMENT || tokens[i]->type == COMMAND)
		{
			u.original = tokens[i]->value;
			if (!expand_variables(&u))
				return (0);
			if (u.result)
			{
				free(tokens[i]->value);
				tokens[i]->value = u.result;
			}
		}
	}
	return (1);
}
