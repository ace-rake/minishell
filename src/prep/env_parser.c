/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:05:51 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/09 15:50:43 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

void	free_env_node(t_env_list *env)
{
	if (!env)
		return ;
	if (env->val)
		free(env->val);
	if (env->var)
		free(env->var);
	free(env);
}

void	free_env(t_env_list *env)
{
	t_env_list *tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;	
	}
}

t_env_list	*env_line_parser(char *env_line)
{
	t_env_list *new;
	char *val;
	short index;

	new = (t_env_list *)malloc((1) * (sizeof(t_env_list *)));
	if (!new)
		return (NULL);
	val = strchr(env_line, '=');
	if (!val)
	{
		free(new);
		return (NULL);
	}
	index = val - env_line;
	val++;
	new->val = ft_strdup(val);
	new->var = ft_substr(env_line, 0, index);
	new->next = NULL;
	new->exported = true;
	if (!new->val || !new->var)
	{
		free_env_node(new);
		return (NULL);
	}
	return (new);
}

void env_add_back(t_env_list **head, t_env_list *to_add)
{
	t_env_list *tmp;

	if (!to_add)
		return ;
	if (!*head)
	{
		*head = to_add;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = to_add;
	return ;
}

t_env_list *env_parser(char *env[])
{
	t_env_list *head;
	int iter;
	
	iter = 0;
	head = NULL;
	while (env[iter])
	{
		env_add_back(&head, env_line_parser(env[iter]));
		iter++;
	}
	return (head);
}