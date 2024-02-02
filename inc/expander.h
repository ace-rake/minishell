/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:03:41 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/02 12:23:56 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "typedefs.h"
# include "../libft/inc/libft.h"

//expander
int	expander(t_token **tokens, t_env_list *env, int exit_status);
//utils
void	init_expander_utils(t_expander_utils *u, t_env_list *env, int exit_status);
void	toggle_single_quote(t_expander_utils *u);
void	toggle_double_quote(t_expander_utils *u);
//questionmark
int	handle_questionmark(t_expander_utils *u);
//environment
int	handle_env_variable(t_expander_utils *u);

#endif
