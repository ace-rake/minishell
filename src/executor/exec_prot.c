#include "../../inc/typedefs.h"
#include "executor.h"

//long line arguments wil be given in a linked list of tokens
//need to make sure to close fds if they would be overwritten
//need to see what can go wrong, and what should happen if something does go wrong

int	exec_pipe(t_token *token)
{
	int	filedes[2];
	int retval;
	t_token *tmp;
	
	retval = pipe(filedes);			//create pipe
	if (retval == -1)
		return (1);

	tmp = token;
	token = token->right;			//here we start with setting the right side input
	while (token->type != COMMAND)	//we search for the command by always going left as the command cant be on the right of a token except if the token is already a command (meaning that we are on the right of a pipe)
		token = token->left;
	token->input = filedes[0];		//set the command of the right side of the syntax tree to use the read end of the pipe as input

	token = tmp;
	token = token->left;			//here we start with setting the output of the left side
	if (token->type == PIPE)		//if we find a pipe, we need to set the output of the right side of that pipe to be the input of the first pipe
		token = token->right;
	while (token->type != COMMAND)	//here we can assume that there are no more pipes to the left, meaning we are in a single command, which we search for by going left
		token = token->left;
	token->output = filedes[1];		//we set the write side of this command to be the input of the pipe
	return (0);
}
/*	exec pipe
 *	RETURN VALUE
 *		the return value is equal to what the return value of the pipe() command was
*/

int	exec_redir_in(t_token *token)
{
	while (token->type != COMMAND)
		token = token->left;
	token->input = open(token->right->value, O_RDONLY);
	return (token->left->input);
}

int	exec_redir_out(t_token *token)
{
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(token->right->value, O_WRONLY|O_CREAT|O_TRUNC);
	return (token->left->output);
}

int	exec_redir_append(t_token *token)
{
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(token->right->value, O_WRONLY|O_APPEND|O_CREAT);
	return (token->left->output);
}

int	exec_command_builtin(t_token *token)
{

}

int	exec_command_file(t_token *token)
{

}

char *return_builtin(t_token *token)
{


}
/*
 * this function will return a function pointer to the corresponding builtin that need to be executed
*/

int	exec_command(t_token *token)
{

}
/*
 *	if no slashes
 * 		1. attempt to execute as is
 * 		2. check if built in
 * 		3. look in path variable
 * 	if any of prev = succes or contains slashes
 * 		execute program is seperate execution env (fork)
 *
 *		
*/

int	execute(t_token *token, t_env_list *env)
{
	if (token->type == PIPE) // |
		return (exec_pipe(token));
	else if (token->type == REDIR_IN) // <
		return (exec_redir_in(token));
	else if (token->type == REDIR_OUT) // >
		return (exec_redir_out(token));
	else if (token->type == REDIR_HEREDOC) // <<
		return (exec_redir_heredoc());
	else if (token->type == REDIR_APPEND) // >>
		return (exec_redir_append(token));
	else if (token->type == COMMAND) // CMD arg
		return (exec_command(token));
	return (1);
}

void	exec_token(t_token *token, t_env_list *env)
{
	if (execute(token, env))
		perror("execute");
	if (token->left && token->left->type != ARGUMENT)
		exec_token(token->left, env);
	if (token->right && token->right->type != ARGUMENT) // this should only happen after a pipe, otherwise the token to the right will always be an argument
		exec_token(token->right, env);
}
