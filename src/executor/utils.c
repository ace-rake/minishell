/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:14 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/22 10:09:22 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int arg_counter(t_token *token)
{
	int	argc = 1;
	while (token->right)
	{
		argc++;
		token = token->right;
	}
	return (argc);
}

char **token_chain_to_array(t_token *token) {
	char **result;
	int argc;
	int iter;
	
	argc = arg_counter(token);
	result = (char **)malloc((argc + 1) * (sizeof(char *)));
	if (!result)
	{
		
	}
	iter = 0;
	while (token)
	{
		result[iter++] = token->value;
		token = token->right;
	}
	result[iter] = NULL;
	return (result);
}

char *get_env_val(t_env_list *env, char *var)
{
	while (env && strcmp(env->var, var) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	return (env->val);
}
/* return the val of a given var from the env list */

char	*get_next_path(char *path_val)
{
	char *sub;
	int index;

	index = ft_strchr(path_val, ':') - path_val;
	sub = ft_substr(path_val, 0, index);
	return (sub);
}
/*
 * test next first path and return it if its correct
 * if the next path wasnt correct, return cmd alone instead
*/

char *check_current_path(char *curr_path, char *cmd)          
{   
    char *tmp;      
    
    tmp = ft_strjoin("/", cmd);                               
    curr_path = ft_strjoin(curr_path, tmp);                   
	free(tmp);
    if (access(curr_path, X_OK) == 0)
	{
        return (curr_path);                                   
	}
	free(curr_path);
    return (NULL);                                            
}   


char *get_full_cmd_path(char *cmd, t_env_list *env)
{
	char *path_val;
	char *retval;
	char *result;

	path_val = get_env_val(env, "PATH");
	if (!path_val)
		return (NULL);
	retval = get_next_path(path_val);
	while (retval)
	{
		result = check_current_path(retval, cmd);
		free(retval);
		if (result)
			return (result);
		while (*path_val != ':' && *path_val)
			path_val++;
		if (*path_val == '\0')
			break;
		else if (*path_val == ':')
			path_val++;
		retval = get_next_path(path_val);
	}
	return (result);
}
/*
 * keep trying pieces of the path val to see if one of them is an actual command
 * return said command if its found or NULL if not
 */
