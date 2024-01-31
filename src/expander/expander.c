/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:03:07 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/30 14:13:36 by wdevries         ###   ########.fr       */
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
	u->variable_name = NULL;
	u->variable_value = NULL;
	u->before = NULL;
	u->after = NULL;
	u->temp = NULL;
}

void	reset_expander_utils(t_expander_utils *u)
{
	u->quoting_status = UNQUOTED;
	u->original = NULL;
	u->result = NULL;
	u->variable_name = NULL;
	u->variable_value = NULL;
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

int	handle_questionmark(t_expander_utils *u)
{
	u->variable_value = ft_itoa(u->exit_status);
	u->before = ft_strndup(u->original, u->i);
	u->after = ft_strdup(u->original + u->i + 2);
	u->result = ft_strjoin(u->before, u->variable_value);
	u->temp = u->result;
	u->result = ft_strjoin(u->temp, u->after);
	free(u->variable_value);
	free(u->before);
	free(u->after);
	free(u->temp);
	u->i += ft_strlen(u->variable_value);
	return (1);
}

int	is_valid_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_variable_name(t_expander_utils *u)
{
	int	start;
	int	len;

	start = u->i + 1;
	len = 0;
	if (!is_valid_start(u->original[start]))
		return (NULL);
	while (u->original[start + len] && is_valid_char(u->original[start + len]))
		len++;
	return (ft_strndup(u->original + start, len));
}

char	*get_variable_value(t_expander_utils *u, char *variable_name)
{
	t_env_list	*current;

	current = u->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, variable_name) == 0)
		{
			if (current->val)
				return (ft_strdup(current->val));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*get_variable(t_expander_utils *u)
{
	u->variable_name = get_variable_name(u);
	if (!u->variable_name)
		return (NULL);
	return (get_variable_value(u, u->variable_name));

}

int	handle_env_variable(t_expander_utils *u)
{
	u->variable_value = get_variable(u);
	if (!u->variable_value)
		return (1);
	u->before = ft_strndup(u->original, u->i);
	u->after = (ft_strdup(u->original + u->i + ft_strlen(u->variable_name) + 1));
	u->result = ft_strjoin(u->before, u->variable_value);
	u->temp = u->result;
	u->result = ft_strjoin(u->temp, u->after);
	free(u->before);
	free(u->after);
	free(u->temp);
	u->i += ft_strlen(u->variable_value - 1);
	return (1);
}

int	handle_dollar_sign(t_expander_utils *u)
{
	if (u->original[u->i + 1] && u->original[u->i + 1] == '?')
		handle_questionmark(u);
	else if (u->original[u->i + 1])
		handle_env_variable(u);
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

int	remove_quotes(t_expander_utils *u, t_token *token)
{
	char	*no_quotes;
	int	i;
	int	j;

	u->quoting_status = UNQUOTED;
	no_quotes = (char *)malloc(sizeof(char) * ft_strlen(token->value));
	if (!no_quotes)
		return (0);
	i = -1;
	j = -1;
	while (token->value[++i])
	{
		if (token->value[i] == '\'' && u->quoting_status != DOUBLE_QUOTED)
			toggle_single_quote(u);
		else if (token->value[i] == '\"' && u->quoting_status != SINGLE_QUOTED)
			toggle_double_quote(u);
		else
			no_quotes[++j] = token->value[i];
	}
	no_quotes[++j] = '\0';	
	free(token->value);
	token->value = no_quotes;
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
			if (!remove_quotes(&u, tokens[i]))
				return (0);
			reset_expander_utils(&u);
		}
	}
	return (1);
}
