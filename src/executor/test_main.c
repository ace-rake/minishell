
#include "executor.h"

void	func(char *env[])
{
	t_env_list *envl = env_parser(env);
	t_token *token = malloc(sizeof(t_token));
	token->type = COMMAND;
	token->value = "PAGERfuck";
	token->output = 1;
	token->input = 0;
	export_builtin(token, envl);

}

void	execve_test_with_option_no_arg(char *env[])
{
	char *path = "/usr/bin/wc";
	char *args[] = {path,"test_main.c","test_main.c",  NULL};

	execve(path, args, env);
}

int	main(int argc, char *argv[], char *env[])
{
	execve_test_with_option_no_arg(env);

}
