/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:07:34 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/22 11:23:27 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "typedefs.h"
# include "../libft/inc/libft.h"
# include <stddef.h>
# include <stdlib.h>

//tokenize.c
int		init_tokenizer_utils(t_tokenizer_utils *u);
t_token	*create_token(char *token_value);
t_token	**add_token(t_tokenizer_utils *u, char *token_value);
t_token **tokenizer(const char *input);

//tokenize_handlers.c
void	handle_special_char(const char *input, t_tokenizer_utils *u);
void	handle_whitespace(const char *input, t_tokenizer_utils *u);
void	handle_single_quote(const char *input, t_tokenizer_utils *u);
void	handle_double_quote(const char *input, t_tokenizer_utils *u);
void	handle_last_token(const char *input, t_tokenizer_utils *u);

#endif
