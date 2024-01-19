/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:16 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/19 15:24:19 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "typedefs.h"
#include "env_parser.h"
#include <errno.h>
#include <sys/wait.h>

#include <string.h>
//delete

#define NOT_EXECUTABLE 129

//this token is the first ARG token
//converts the chain of token ARGS to a single array
//only the char ** needs freeing, as all the char * are pointers to the token values
char **token_chain_to_array(t_token *token);

//this token is the cmd token
int	exec_command_file(t_token *token, t_env_list *env);

char *get_full_cmd_path(char *cmd, t_env_list *env);

void	exec_token(t_token *token, t_env_list *env);

int	env_builtin(t_token *token, t_env_list *env);
int	cd_builtin(t_token *token, t_env_list *env);
int	pwd_builtin(t_token *token);
int		echo_builtin(t_token *token);
void	exit_builtin(t_token *token, t_env_list *env);
int	unset_builtin(t_token *token, t_env_list *env);
int	export_builtin(t_token *token, t_env_list *env);

char *get_env_val(t_env_list *env, char *var);
#endif
