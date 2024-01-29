/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:03:41 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/29 13:20:40 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "typedefs.h"
# include "../libft/inc/libft.h"

void	init_expander_utils(t_expander_utils *u, t_env_list *env, int exit_status);
void	toggle_single_quote(t_expander_utils *u);
void	toggle_double_quote(t_expander_utils *u);
int	handle_dollar_sign(t_expander_utils *u);
int	expand_variables(t_expander_utils *u);
int	expander(t_token **tokens, t_env_list *env, int exit_status);

#endif
