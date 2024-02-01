#include "../inc/minishell.h"

volatile sig_atomic_t g_in_command = 0;

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	if (!g_in_command)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	cmd_main(char *file_name, char *envs[], bool wait)
{
    t_token **tokens;
    t_token *ast_head;
	t_env_list *env;
	char input[1024];
	char *str;
	int	exit_status;
	int monitor;
	FILE *file = fopen(file_name, "r" );

	exit_status = 0;
	env = env_parser(envs);
	while (1)
	{
		tokens = NULL;
		ast_head = NULL;
		fscanf(file, "%[^\n]\n", input);
		printf("\ntesting line [%s]\n", input);
		add_history(input);
		monitor = tokenizer(input, &tokens);
		if (monitor)
			monitor = lexer(tokens);
		if (monitor)
			monitor = parser(tokens, &ast_head);
		if (monitor)
			monitor = expander(tokens, env, exit_status);
		if (monitor)	
			exit_status = executor(ast_head, env);
		/* printf("retval main : [%i]\n",retval); */	
		free_tokens(tokens);
		if (wait)
		{
			str = readline("\nnext ? [q to stop]");
			if (ft_strcmp(str, "q") == 0)
				exit (0);
			str = 0;
		}
	}
	free_env(env);

	return (0);
}

int main(int argc, char **argv, char *envs[]) {
	/* rl_catch_signals = 0; */
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
		cmd_main("commands_no_wait.txt",envs, false);
	else
		cmd_main("commands.txt", envs, true);
	(void)argc;
	(void)argv;
	(void)envs;
}
