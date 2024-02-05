/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:06:54 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/05 15:27:46 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* const char	*remove_quotes_heredoc(const char *value) */
/* { */
/* 	t_expander_utils	u; */

/* 	init_expander_utils(&u, env); */
	 
/* } */

int	read_heredoc(t_token *token)
{
	char	*str;
	int		filedes[2];
	/* bool	expand_variables; */
	/* const char *deliminator; */


	if (pipe(filedes) == -1)
		return (1);
	token->input = filedes[0];
	/* if (!ft_strchr((const char *)token->right->value, "\"") && !ft_strchr((const char *)token->right->value, "\'")) */
	/* { */
	/* 	deliminator = (const char *)token->right->value; */
	/* 	expand_variables = true; */
	/* } */
	/* else */
	/* { */
	/* 	deliminator = remove_quotes_heredoc((const char *)token->right->value); */
	/* 	expand_variables = false; */
	/* } */
	str = readline(">");
	while (ft_strcmp(str, (const char *)token->right->value) != 0)
	{
		ft_putendl_fd(str, filedes[1]);
		str = readline(">");
	}
	ft_putchar_fd('\0', filedes[1]);
	close(filedes[1]);
	return (0);
}

int	exec_heredocs(t_token *head)
{
	if (head->left)
		exec_heredocs(head->left);
	if (head->right)
		exec_heredocs(head->right);
	if (head->type == REDIR_HEREDOC)
		read_heredoc(head);
	return (0);
}

/*
 * read line
 * check if VALUE
 * if not value
 * 		write \n for prev line 
 * 		and write own line
 */
