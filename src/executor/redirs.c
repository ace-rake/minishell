/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:53:09 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/31 11:10:50 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_pipe(t_token *token)
{
	int		filedes[2];
	int		retval;
	t_token	*tmp;

	retval = pipe(filedes);
	if (retval == -1)
		return (1);
	tmp = token;
	token = token->right;
	while (token->type != COMMAND)
		token = token->left;
	token->input = filedes[0];
	token = tmp;
	token = token->left;
	if (token->type == PIPE)
		token = token->right;
	while (token->type != COMMAND)
		token = token->left;
	token->output = filedes[1];
	tmp->input = filedes[0];
	tmp->output = filedes[1];
	return (0);
}

//exec pipe
//	RETURN VALUE
// here we start with setting the right side input
// we search for the command
// 	by always going left as the command cant be on the right of a token
// 		except if the token is already a command
// 			(meaning that we are on the right of a pipe)
// set the command of the right side of the syntax tree
// 	to use the read end of the pipe as input
// here we start with setting the output of the left side
// we need to set the output of the right side of that pipe
// 	to be the input of the first pipe
// here we can assume that there are no more pipes to the left,
// meaning we are in a single command, which we search for by going left
// we set the output side of this command to be the write end of the pipe
//	the return value is equal to what the return value of the pipe() command was
int	exec_redir_in(t_token *token)
{
	char	*file;
	t_token	*redir;

	redir = token;
	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->input = open(file, O_RDONLY);
	redir->input = token->input;
	if (redir->input == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}

int	exec_redir_out(t_token *token)
{
	char	*file;
	t_token	*redir;

	redir = token;
	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	redir->output = token->output;
	if (redir->output == -1)
		return (-1);
	return (0);
}

int	exec_redir_append(t_token *token)
{
	char	*file;
	t_token	*redir;

	redir = token;
	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(file, O_WRONLY | O_APPEND | O_CREAT);
	redir->output = token->output;
	if (redir->output == -1)
		return (-1);
	return (0);
}

int	exec_redir_heredoc(t_token *token)
{
	t_token	*redir;

	redir = token;
	while (token->type != COMMAND)
		token = token->left;
	token->input = redir->input;
	return (0);
}
/*
 *	I think heredoc should be done before executing
 *	Reason : 
 *		if you run "cat << EOF > outfile"
 *		according to execution rules,
			outfile should be generated before the heredoc is initiated
 *		However
 *		If you cancel heredoc with control
			+ c then you can see that the outfile is in fact not generated yet
 *
 *		if heredoc happens in a previous step,
			it would be logical to store the fd
				from which i need to reed inside of the heredoc token,
			so i can just copy that into the correct token
 */
