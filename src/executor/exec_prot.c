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
	char *file;

	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->input = open(file, O_RDONLY);
	return (token->left->input);
}

int	exec_redir_out(t_token *token)
{
	char *file;

	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(file, O_WRONLY|O_CREAT|O_TRUNC);
	return (token->left->output);
}

int	exec_redir_append(t_token *token)
{
	char *file;

	file = token->right->value;
	while (token->type != COMMAND)
		token = token->left;
	token->output = open(file, O_WRONLY|O_APPEND|O_CREAT);
	return (token->left->output);
}
/*
int	exec_command_as_is(t_token *token)
{
	return (1);
}
*/
int	exec_redir_heredoc(t_token *token)
{

	return (1);
}

int	exec_command_builtin(t_token *token, t_env_list *env)
{
	if (strncmp(token->value, "echo\0", 5))
		echo_builtin(token);
	else if (strncmp(token->value, "cd\0", 3))
		cd_builtin(token, env);
	else if (strncmp(token->value, "pwd\0", 4))
		pwd_builtin(token);
	else if (strncmp(token->value, "export\0", 7))
		export_builtin(token, env);
	else if (strncmp(token->value, "unset\0", 6))
		unset_builtin(token, env);
	else if (strncmp(token->value, "env\0", 4))
		env_builtin(token, env);
	else if (strncmp(token->value, "exit\0", 5))
		exit_builtin(token);
	return (0);
}


/*
 * this function will return a function pointer to the corresponding builtin that need to be executed
*/

int	exec_command(t_token *token, t_env_list *env)
{
/*	if (!exec_command_as_is(token))
		return (0);
	//try execute as is here
	//if fail
*/	if (!exec_command_builtin(token, env))
		return (0);
	//check built in here
	//if fail
	if (!exec_command_file(token, env))
		return (0);
	return (NOT_EXECUTABLE);
}
/*
 *	if no slashes
 * 		1. attempt to execute as is, ig to see if that executable just exists in working directory
 * 		2. check if built in
 * 		3. look in $path
 * 	if any of prev = succes or contains slashes
 * 		execute program is seperate execution env (fork)
 *
 * 	im gonna reduce this to
 * 		1. execute as is
 * 		2. try execute as builtin
 * 		3. try execute from $path
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
		return (exec_redir_heredoc(token));
	else if (token->type == REDIR_APPEND) // >>
		return (exec_redir_append(token));
	else if (token->type == COMMAND) // CMD arg
		return (exec_command(token, env));
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
