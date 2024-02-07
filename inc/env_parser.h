/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:02:08 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 13:02:10 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PARSER_H
# define ENV_PARSER_H

# include "executor.h"
# include "typedefs.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

t_env_list	*env_parser(char *env[]);
void		free_env_node(t_env_list *env);
void		free_env(t_env_list *env);
t_env_list	*del_node(t_env_list **head, t_env_list *to_del);
t_env_list	*get_env_node(t_env_list *head, char *var);
void		env_add_back(t_env_list **head, t_env_list *to_add);
t_env_list	*env_node_con(char *var, char *val, bool exported);

int			read_heredoc(t_token *token, t_env_list *env);
int			exec_heredocs(t_token *head, t_env_list *env);
int			set_here_filedes(t_token *token);

#endif
