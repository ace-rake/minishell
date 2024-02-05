#include "../inc/minishell.h"

t_mini	g_mini;

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	g_mini.exit_status = 130;
	if (!g_mini.in_command)
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
	int monitor;
	char input[1024];
	char *str;
	FILE *file = fopen(file_name, "r" );

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
			monitor = expander(tokens, env);
		if (monitor)	
			g_mini.exit_status = executor(tokens, ast_head, env);
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
	printf("choices :\n1 : run all comands rapid fire\n2 : run all commands step by step\n3 : run non input commands rapid fire\n4 : run non input commands step by step\n");
	char *str = readline("choice");
	int option = ft_atoi(str);
	if (option == 1)
		cmd_main("commands.txt",envs, false);
	if (option == 2)
		cmd_main("commands.txt",envs, true);
	if (option == 3)
		cmd_main("commands_no_wait.txt",envs, false);
	if (option == 4)
		cmd_main("commands_no_wait.txt",envs, true);
	(void)argc;
	(void)argv;
	(void)envs;
}
