#include "../../inc/typedefs.h"
#include "executor.h"

//long line arguments wil be given in a linked list of tokens

int	exec_pipe(t_token *token)
{
	int	filedes[2];
	int retval;
	
	retval = pipe(filedes);

	token->left->output = filedes[1];
	token->right->input = filedes[0];
	return (retval);
}

int	exec_redir_in(t_token *token)
{
	token->left->input = open(token->right->value, O_RDONLY);
	return (token->left->input);
}

int	exec_redir_out(t_token *token)
{
	token->left->output = open(token->right->value, O_WRONLY);
	return (token->left->output);
}

int	exec_redir_append(t_token *token)
{
	token->left->output = open(token->right->value, O_WRONLY|O_APPEND);
	return (token->left->output);
}

int	exec_command_builtin(t_token *token)
{

}

int	exec_command_file(t_token *token)
{

}

int	exec_command(t_token *token)
{
	//check if built int or executable file
	


}

void	execute(t_token *token)
{
	if (token->type == PIPE) // |
		exec_pipe(token);
	else if (token->type == REDIR_IN) // <
		exec_redir_in(token);
	else if (token->type == REDIR_OUT) // >
		exec_redir_out(token);
	else if (token->type == REDIR_HEREDOC) // <<
		exec_redir_heredoc();
	else if (token->type == REDIR_APPEND) // >>
		exec_redir_append(token);
	else if (token->type == COMMAND) // CMD arg
		exec_command(token);
}

void	exec_token(t_token *token){
	execute(token);

	if (token->left && token->left->type != ARGUMENT)
		exec_token(token->left);
	if (token->right)
		exec_token(token->right);
}
