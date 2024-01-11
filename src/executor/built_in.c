/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:19 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/11 15:33:50 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
• Your shell must implement the following builtins:
DONE◦ echo with option -n
DONE◦ cd with only a relative or absolute path
DONE◦ pwd with no options
DONE◦ export with no options 		#need to have variable list for this
DONE◦ unset with no options			#need to have variable list for this
DONE◦ env with no options or arguments	#need to have variable lsit for this
◦ exit with no options man i dunno
*/

static int	set_fd(t_token *token)
{
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

void	print_export(t_token *token, t_env_list *env)
{
	while (env)
	{
		if (env->exported == true)
		{
			ft_putstr_fd("declare -x ", token->output);
			ft_putstr_fd(env->var, token->output);
			ft_putchar_fd('=', token->output);
			ft_putchar_fd('"', token->output);
			ft_putstr_fd(env->val, token->output);
			ft_putchar_fd('"', token->output);
			ft_putchar_fd('\n', token->output);
		}
		env = env->next;
	}
}

void	export_builtin(t_token *token, t_env_list *env)
{
	if (!token->right)
		print_export(token, env);
	else
	{
		while (token->right)
		{
			token = token->right;
			char *val = ft_strchr(token->value, '=');
			if (val)
			{
				char *var = ft_substr(token->value, 0, val - token->value);
				env_add_back(&env, env_node_con(var,++val,true));
				free(var);
			}
			else
			{
				t_env_list *node = get_env_node(env, token->value);
				if (node)
					node->exported = true;
			}
		}
	}
}
//check if no args
//try to export for each arg token,
//for each token
// 1.look for = sign
//	if = is found
//		create new variable with corresponding values and set export=true
//	if = is ! found
//		find env variable by name value and set corresponding export=true

void	unset_builtin(t_token *token, t_env_list *env) //cmd token
{
	t_env_list *to_del;
	
	while (token->right)
	{
		token = token->right;
		set_fd(token);
		to_del = get_env_node(env, token->value);
		if (to_del)
			del_node(&env, to_del);
	}
}
//TODO this doesnt actually do anything if there is a pipe behind this cmd
//this also count for export

void	exit_builtin(t_token *token)
{

}

void	cd_builtin(t_token *token, t_env_list *env)
{
	int retval;
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
	retval = chdir(token->right->value);
	if (retval != 0)
		perror("cd_builtin");
}

void	pwd_builtin(t_token *token)
{
	char *retval;
	set_fd(token);
	retval = getcwd(NULL, 0);
	if (!retval)
	{
		perror("pwd_builtin");
		return ;
	}
	ft_printf("%s\n",retval);
	free(retval);
}

void	echo_builtin(t_token *token)
{
	bool	option;

	set_fd(token);
	option = false;
	if (ft_strncmp(token->right->value, "-n\0", 3) == 0)
	{
		option = true;
		token = token->right;
	}
	char **token_chain = token_chain_to_array(token->right);
	//can fail
	int iter = 0;
	while (token_chain[iter])
		ft_putstr_fd(token_chain[iter], token->output);
}
//still need to add the optional option check for -n

void	env_builtin(t_token *token, t_env_list *env)
{
	set_fd(token);
	while (env)
	{
		if (env->exported == true)
		{
			ft_putstr_fd(env->var, token->output);
			ft_putchar_fd('=', token->output);
			ft_putendl_fd(env->val, token->output);
		}
		env = env->next;
	}
}
/*
*/
