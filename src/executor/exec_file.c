/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:23:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:54 by vdenisse         ###   ########.fr       */
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
	char *cmd_path;

	//used for execve and child
	if (ft_strchr(token->value, '/') == NULL)
		cmd_path = get_full_cmd_path(token->value, env);
	else
		cmd_path = token->value;
	char **args = token_chain_to_array(token);


	pid_t child;

	child = fork();
	if (child == 0)
		exec_child(token, cmd_path, args);
	return (1);
}
