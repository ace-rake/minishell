/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:28:01 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/26 13:29:16 by vdenisse         ###   ########.fr       */
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

int	append_to_var(t_env_list *env,char *val_to_append, char *var)
{
	t_env_list *node;
	char *tmp;

	node = get_env_node(env, var);
	tmp = node->val;
	node->val = ft_strjoin(tmp, val_to_append);
	free(tmp);
	return (0);
}

int	old(t_token *token, t_env_list *env)
{
	t_token *tmp;
	char *val;
	char *var;
	int	append;
	t_env_list *node;

	tmp = token;
	while (tmp->parent)
		tmp = tmp->parent;
	if (tmp->type == PIPE)
		return (0);
	if (!token->right)
		print_export(token, env);
	else
	{
		while (token->right)
		{
			token = token->right;
			val = ft_strchr(token->value, '=');
			append = 0;
			if (val - 1 && *(val - 1) == '+')
				append = 1;
			if (val)
			{
				var = ft_substr(token->value, 0, val - token->value - append);
				val++;
				node = get_env_node(env, var);
				if (!node)
					env_add_back(&env, env_node_con(var,val,true));
				else if (append)
					append_to_var(env, val, var);
				else
				{
					free(node->val);
					node->val = ft_strdup(val);
				}
				free(var);
			}
			else
			{
				node = get_env_node(env, token->value);
				if (node)
					node->exported = true;
			}
		}
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
	(void)token;
	return (false);
}

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

	if (check_elder_parent(token) | syntax_check(token))
		return (0);
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
