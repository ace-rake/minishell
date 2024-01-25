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

int	loop_main(char *envs[])
{
    t_token **tokens;
    t_token *ast_head;
	t_env_list *env;
	char *input;
	int	exit_status;
	int monitor;

	exit_status = 0;
	env = env_parser(envs);
	while (1)
	{
		tokens = NULL;
		ast_head = NULL;
		input = readline("minishell: ");
		if (!input) //ctrl-D
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, "") == 0) //empty input
		{
			free(input);
			continue ;
		}
		add_history(input);
		monitor = tokenizer(input, &tokens);
		if (monitor)
			monitor = lexer(tokens);
		if (monitor)
			monitor = parser(tokens, &ast_head);
		/* if (monitor) */
			/* monitor = expander(tokens, exit_status); */
		if (monitor)	
			exit_status = executor(ast_head, env);
		/* printf("retval main : [%i]\n",retval); */	
		free(input);
		free_tokens(tokens);
	}
	free_env(env);
	return (0);
}

int main(int argc, char **argv, char *envs[]) {
	/* rl_catch_signals = 0; */
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (loop_main(envs));
	(void)argc;
	(void)argv;
	(void)envs;
}
