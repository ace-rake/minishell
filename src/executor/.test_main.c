
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

t_token *token_con(char *value, int output, int input)
{
	t_token *token = malloc(sizeof(t_token));
	token->value = value;
	token->input =input;
	token->output = output;
	token->parent = NULL;
	token->right = NULL;
	token->left = NULL;
	return token;
}

void	print_cwd()
{
	char *str = malloc(sizeof(char) * 200);
	size_t n = 200;
	str = getcwd(str, n);
	printf("%s", str);
}

void	simple_token_test(int argc, char *cmds[], char *envs[])
{
	if (argc <= 1)
	{
		printf("Fuck You\n");
		return ;
	}

	t_env_list *env = env_parser(envs);

	t_token *cmd = token_con(cmds[1], 1, 0);
	cmd->type = COMMAND;
	t_token *head = cmd;
	for (int i = 2; cmds[i]; ++i)
	{
		cmd->right = token_con(cmds[i], 1, 0);
		cmd = cmd->right;
		cmd->type = ARGUMENT;
		cmd->right = NULL;
	}
	exec_token(head,env);
	while (head)
	{
		t_token *tmp = head->right;
		free(head);
		head = tmp;
	}
	free_env(env);
	print_cwd();
}

void	heredoc_test(char *env[])
{
	t_env_list *envl = env_parser(env);
	t_token *here = token_con("EOF", 1, 0);
	t_token *arg = token_con("EOF", 1, 0);
	here->right = arg;
	here->type = REDIR_HEREDOC;
	read_heredoc(here);

	t_token *cmd = token_con("cat", 1, 0);
	cmd->type = COMMAND;
	here->left = cmd;
	exec_token(here, envl);
}

int	main(int argc, char *argv[], char *env[])
{
	heredoc_test(env);
}
