/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:19 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/26 13:22:52 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
• Your shell must implement the following builtins:
DONE◦ echo with option -n
DONE◦ cd with only a relative or absolute path
DONE◦ pwd with no options
DONE◦ export with no options 		#need to have variable list for this
DONE◦ unset with no options			#need to have variable list for this
DONE◦ env with no options or arguments	#need to have variable lsit for this
DONE◦ exit with no options man i dunno
*/

static int	set_fd(t_token *token)
{
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}


int	unset_builtin(t_token *token, t_env_list *env) //cmd token
{
	t_env_list *to_del;
	t_token *tmp;

	tmp = token;
	while (tmp->parent)
		tmp = tmp->parent;
	if (tmp->type == PIPE)
		return (0);
	while (token->right)
	{
		token = token->right;
		set_fd(token);
		to_del = get_env_node(env, token->value);
		if (to_del)
			del_node(&env, to_del);
	}
	return (0);
}
//TODO this doesnt actually do anything if there is a pipe behind this cmd
//this also count for export
//fix added check to see if top token is pipe, if so dont execute at all
//	TODO: look for syntax errors


int	exit_builtin(t_token *token, t_env_list *env)
{
	while (token->parent)
		token = token->parent;
	//it doesnt matter if im on the left or right side, if i just go up until im at the origin token i can just check that token to see if there were any pipes at all
	//this also resets the token to the origin because im assuming the free_tokens command will take that token
	if (token->type == PIPE)
		return (0) ;
	free_env(env);
	free_ast_tree(token);
	if (!token->right)
		exit(0);
	exit(ft_atoi(token->right->value));
}
//this function will be made to exit only when the exit command is called, dont use it for non command-execution reasons
//exit doesnt do anything if there is a pipe somewhere
//TODO free_tokens fucntions ig
//everything else works as expected me thinks
//	TODO: look for syntax errors

int	cd_builtin(t_token *token, t_env_list *env)
{
	char *path;

	set_fd(token);
	if (token->right)
		path = token->right->value;
	else
	{
		path = get_env_val(env, "HOME");
		if (!path)
		{
			ft_putstr_fd("bash : cd: HOME not set", 1);
		}
	}
	if (chdir(token->right->value) == -1)
		return (1);
	return (0);
}

int	pwd_builtin(t_token *token)
{
	char *retval;
	set_fd(token);
	retval = getcwd(NULL, 0);
	if (!retval)
	{
		return (errno) ;
	}
	ft_printf("%s\n",retval);
	free(retval);
	return (0);
}

int	echo_builtin(t_token *token)
{
	bool	option;

	set_fd(token);
	option = false;
	if (token->right && ft_strncmp(token->right->value, "-n\0", 3) == 0)
	{
		option = true;
		token = token->right;
	}
	if (token->right)
	{
		char **token_chain = NULL;
		token_chain = token_chain_to_array(token->right);
	//can fail
		int iter = 0;
		while (token_chain && token_chain[iter])
		{
			ft_putstr_fd(token_chain[iter], token->output);
			if (token_chain[++iter])
				ft_putchar_fd(' ', token->output);
		}
		free(token_chain);
	}
	if (!option)
		write(1, "\n", token->output);
	return (0);
}
//still need to add the optional option check for -n
//DONE need to put spaces in between all the arguments
//except when there is no space but quotes

int	env_builtin(t_token *token, t_env_list *env)
{
	if (get_env_node(env, "PATH") == NULL)
		return (127);
	set_fd(token);
	while (env)
	{
		if (env->exported == true && env->val)
		{
			ft_putstr_fd(env->var, token->output);
			ft_putchar_fd('=', token->output);
			ft_putendl_fd(env->val, token->output);
		}
		env = env->next;
	}
	return (0);
}
