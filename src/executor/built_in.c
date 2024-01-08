/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:19 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/08 14:43:29 by vdenisse         ###   ########.fr       */
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

void	cd_builtin(t_token *token)//this token is still the command token
{
	int retval;

	retval = chdir(token->left->value);
	if (retval != 0)
		perror("cd_builtin");
}

void	pwd_builtin(void)
{
	char *retval;
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

}
