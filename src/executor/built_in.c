/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:19 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/10 13:34:22 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
• Your shell must implement the following builtins:
◦ echo with option -n
DONE◦ cd with only a relative or absolute path
DONE◦ pwd with no options
◦ export with no options 		#need to have variable list for this
◦ unset with no options			#need to have variable list for this
◦ env with no options or arguments	#need to have variable lsit for this
◦ exit with no options
*/

int	set_fd(t_token *token)
{
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

void	cd_builtin(t_token *token)//this token is still the command token
{
	int retval;

	set_fd(token);
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
	printf("%s\n",retval);
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
		ft_putstr_fd(env->var, token->output);
		ft_putchar_fd('=', token->output);
		ft_putendl_fd(env->val, token->output);
		env = env->next;
	}
}
/*
int	main(int argc, char *argv[], char *env[])
{
	t_env_list *envl = env_parser(env);
	t_token *token = malloc(sizeof(t_token));
	token->type = COMMAND;
	token->value = "env";
	token->output = 1;
	token->input = 0;
//	env_builtin(token, envl);
	for (int i = 0; env[i]; ++i)
		printf("%s\n", env[i]);
}
*/
