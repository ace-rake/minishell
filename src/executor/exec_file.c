/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:23:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/10 11:37:28 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_child(t_token *token, char *cmd_path, char **args)
{
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output, STDOUT_FILENO) == -1 )
		exit(errno);
	execve(cmd_path, args,NULL);
	exit(1);
}

int	exec_command_file(t_token *token, t_env_list *env)
{

	//used for execve and child
	char *cmd_path = get_full_cmd_path(token->value, env);
	char **args = token_chain_to_array(token);


	pid_t child;

	child = fork();
	if (child == 0)
		exec_child(token, cmd_path, args);
	return (1);
}
