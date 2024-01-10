/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:27:25 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/10 13:41:32 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../typedefs.h"


t_token	*parser(t_token **tokens);
t_token	*parse_pipes(t_token **tokens);
t_token	*parse_pipes(t_token **tokens);
t_token	*parse_commands(t_token **tokens);
t_token	*parse_arguments(t_token **tokens);
//util
int	token_is_redirection(t_token *token);

# endif
