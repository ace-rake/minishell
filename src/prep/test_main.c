#include "env_parser.h"

int	main(int argc, char *argv[], char *env[])
{
	t_env_list *env_list  = env_parser(env);
	t_token *token = malloc(sizeof(t_token));
	token->type = COMMAND;
	token->value = "env";
	token->output = open("create_test", O_WRONLY|O_CREAT);
	token->input = 0;
	env_builtin(token, env_list);
}
