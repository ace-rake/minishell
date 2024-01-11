
#include "executor.h"

int	main(int argc, char *argv[], char *env[])
{
	t_env_list *envl = env_parser(env);
	t_token *token = malloc(sizeof(t_token));
	token->type = COMMAND;
	token->value = "PAGERfuck";
	token->output = 1;
	token->input = 0;
	export_builtin(token, envl);
}
