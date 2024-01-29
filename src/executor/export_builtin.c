/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:28:01 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 11:58:20 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_export(t_token *token, t_env_list *env)
{
	while (env)
	{
		if (env->exported == true)
		{
			ft_putstr_fd("declare -x ", token->output);
			ft_putstr_fd(env->var, token->output);
			if (env->val != NULL)
			{
				ft_putchar_fd('=', token->output);
				ft_putchar_fd('"', token->output);
				ft_putstr_fd(env->val, token->output);
				ft_putchar_fd('"', token->output);
			}
			ft_putchar_fd('\n', token->output);
		}
		env = env->next;
	}
	return (0);
}

bool	check_elder_parent(t_token *token)
{
	while (token->parent)
		token = token->parent;
	if (token->type == PIPE)
		return (true);
	return (false);
}

bool	syntax_check(t_token *token)
{
	char *valid;
	int index;
	bool retval;

	retval = false;
	if (!token)
		return (retval);
	valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	if (ft_strchr(valid, token->value[0]) == NULL)
		retval = true;
	valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_123456789";
	index = 0;
	while (!retval && token->value[++index] && token->value[index] != '=')
		if (ft_strchr(valid, token->value[index]) == NULL)
			retval = true;
	if (retval)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->parent->value, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	return (retval);
}
/*
 * tings to shek
 *		START with beeg or smoll letta or with undascore
 *	after first
 *		can be any letta, numba, undascore
 *
 */

int	get_var_and_val(char **var, char **val, t_token *token)
{
	int	type;

	type = 2; // default export var=val type
	if (!token)
		return (0);
	*val = ft_strchr(token->value, '=');
	if (!*val) // export var type
	{
		*var = ft_strdup(token->value);
		return (1);
	}
	if (*(*val - 1) == '+') // export var+=val type
		type = 3;
	if (type == 3)
		*var = ft_substr(token->value, 0, *val - token->value - 1);
	else
		*var = ft_substr(token->value, 0, *val - token->value);
	(*val)++;
	*val = ft_strdup(*val);
	return (type);
}

int	handle_3(t_env_list *node, char *val)
{
	char *tmp;

	tmp = ft_strjoin(node->val, val);
	free(node->val);
	node->val = tmp;
	return (0);
}

int	handle_2(t_env_list *env, t_env_list *node, char *var, char *val)
{
	if (node)
	{
		if (node->val)
			free(node->val);
		if (node->var)//node->var shold always exist
			free(node->var);
		node->var = ft_strdup(var);
		node->val = ft_strdup(val);
	}
	else
		env_add_back(&env, env_node_con(var,val,1));
	return (0);
}

int	handle_1(t_env_list *env, t_env_list *node, char *var)
{
	if (node)
		node->exported = true;
	else
		env_add_back(&env, env_node_con(var,NULL,1));
	return (0);
}

int	export_builtin(t_token *token, t_env_list *env, bool export)
{
	char *val;
	char *var;
	int	type;
	t_env_list *node;

	if (check_elder_parent(token))
		return (0);
	if (syntax_check(token->right))
	{
		return (1);
	}
	type = get_var_and_val(&var, &val, token->right);
	if (type == 0)
		return (print_export(token, env));
	node = get_env_node(env, var);
	if (type == 1)
		handle_1(env, node, var);
	else if (type == 2 || !node)
		handle_2(env, node, var, val);
	else
		handle_3(node, val);
	if (var)
		free(var);
	if (val)
		free(val);
	(void)export;
	return (0);
}
//new plan of action
//	first things first check the syntax
//
//could add a export boolean parameter, that way i could use export for set also
//
//all different cases
//	if elder parent == "|"
//		do nothing
//	if = is preset
//		if  + is before = 
//			set append = true
//		if "var" exists
//			overwrite or append var with new val
//		else
//			create new env_list node
//	
//

//check if no args
//try to export for each arg token,
//for each token
// 1.look for = sign
//	if = is found
//		create new variable with corresponding values and set export=true
//	if = is ! found
//		find env variable by name value and set corresponding export=true
//	TODO: look for syntax errors
