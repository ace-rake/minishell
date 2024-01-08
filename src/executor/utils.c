/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:14 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/08 14:44:10 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int arg_counter(t_token *token)
{
	int	argc = 0;
	while (token->right)
		argc++;
	return (argc);
}

char **token_chain_to_array(t_token *token) {
	char **result;
	int argc;
	int iter;
	
	argc = arg_counter(token);
	result = (char **)malloc((argc + 1) * (sizeof(char *)));
	if (!result)
	{
		
	}
	iter = 0;
	while (token)
	{
		result[iter] = token->value;
		token = token->right;
	}
	return (result);
}
