/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:28:01 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/26 10:28:57 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

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

int	export_builtin(t_token *token, t_env_list *env)
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
//check if no args
//try to export for each arg token,
//for each token
// 1.look for = sign
//	if = is found
//		create new variable with corresponding values and set export=true
//	if = is ! found
//		find env variable by name value and set corresponding export=true
//	TODO: look for syntax errors
