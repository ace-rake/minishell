/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:23:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 10:22:42 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_child(t_token *token, char *cmd_path, char **args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output, STDOUT_FILENO) == -1 )
		exit(errno);
	execve(cmd_path, args,NULL);
	exit(127);
}


int check_child(int *child_status)                                    
{
    if (WIFEXITED(*child_status))
    {
        *child_status = WEXITSTATUS(*child_status);
        if (*child_status != 0)
            return (1);
    }
    return (0);
}

int	exec_command_file(t_token *token, t_env_list *env)
{
	char *cmd_path;
	int status;

	//used for execve and child
	if (ft_strchr(token->value, '/') == NULL)
		cmd_path = get_full_cmd_path(token->value, env);
	else
		cmd_path = token->value;
    /*                                                            
     * check if the given token->value has a slash, if so we must use that as the command as is                                     
     * else we will try to find a suitable path in the $path should it (and $path) exist                                            
     */                                                           
    t_token token_tmp;                                            
    token_tmp.value = cmd_path;                                   
    token_tmp.right = token->right;                               
                                                                  
    char **args = token_chain_to_array(&token_tmp);               
    /*                                                            
     * these will be our execve arguments                         
     * these start from the command itself cuz we need that       
     * TODO actually this is still kinda fucked because the first argument should be the full path to the command but as it stands it always uses the token->value of the command                     
     * TMP_FIX: create tmp token with full path to replace the actual command token                                                 
	 * token doesnt need freeing ig
     */                                                           

	pid_t child;

	g_in_command = 1;
	child = fork();
	status = 0;
	if (child == 0)
		exec_child(token, cmd_path, args);
	else if (child > 0)
	{
		waitpid(child, &status, 0);
		g_in_command = 0;
		free(cmd_path);
		free(args);
		check_child(&status);
	}
	if (status == 14)
		ft_printf("status : [%i]\n%s: command not found\n",status,  token->value);
	return (status);
}

