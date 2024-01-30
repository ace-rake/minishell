/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:16:24 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/30 11:48:56 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	echo_check_option(t_token **token, bool *option)
{
	int	index;

	if (!(*token)->right)
		return (0);
	index = 0;
	if ((*token)->right->value[0] == '-')
	{
		while ((*token)->right->value[++index] != '\0')
		{
			if ((*token)->right->value[index] != 'n')
				*option = false;
			else
				*option = true;
		}
	}
	if (*option)
		*token = (*token)->right;
	return (0);
}

int	echo_builtin(t_token *token)
{
	bool	option;
	char	**token_chain;
	int		iter;

	option = false;
	echo_check_option(&token, &option);
	if (token->right)
	{
		token_chain = NULL;
		token_chain = token_chain_to_array(token->right);
		iter = 0;
		while (token_chain && token_chain[iter])
		{
			ft_putstr_fd(token_chain[iter], token->output);
			if (token_chain[++iter])
				ft_putchar_fd(' ', token->output);
		}
		free(token_chain);
	}
	if (!option)
		write(token->output, "\n", 1);
	return (0);
}
//TODO token_chain_to_array can fail
//TODO options can be formatted as such "-nnnnn"
//	but wont do anything if there is another option present eg:"-nnnp"
//still need to add the optional option check for -n
//DONE need to put spaces in between all the arguments
//except when there is no space but quotes
