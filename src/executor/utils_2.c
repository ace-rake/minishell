/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:36:10 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 13:36:59 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_elder_parent(t_token *token)
{
	while (token->parent)
		token = token->parent;
	if (token->type == PIPE)
		return (true);
	return (false);
}

bool	syntax_check(t_token *token)
{
	char	*valid;
	int		index;
	bool	retval;

	retval = false;
	if (!token)
		return (retval);
	valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	if (ft_strchr(valid, token->value[0]) == NULL)
		retval = true;
	valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_123456789";
	index = 0;
	while (!retval && token->value[++index] && token->value[index] != '=')
		if (ft_strchr(valid, token->value[index]) == NULL)
			retval = true;
	if (retval)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->parent->value, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	return (retval);
}
