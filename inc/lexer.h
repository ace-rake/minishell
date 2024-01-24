/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:05:58 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/24 10:42:31 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

t_token	**lexer(t_token **tokens);
bool	syntax_ok(t_token **tokens);
int	token_is_redirection(t_token *token);

#endif
