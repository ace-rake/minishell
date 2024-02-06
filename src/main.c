#include "../inc/minishell.h"

t_mini	g_mini;

int	loop_main(char *envs[])
{
    t_token **tokens;
    t_token *ast_head;
	t_env_list *env;
	char *input;
	int monitor;


	env = env_parser(envs);
	while (1)
	{
		signal(SIGINT, sigint_handler);
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
		free(input);
		if (monitor)
			monitor = lexer(tokens);
		if (monitor)
			monitor = parser(tokens, &ast_head);
		if (monitor)
			monitor = expander(tokens, env);
		if (monitor)	
			g_mini.exit_status = executor(tokens, ast_head, env);
		free_tokens(tokens);
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

int main(int argc, char **argv, char *envs[]) {
	signal(SIGQUIT, SIG_IGN);
	g_mini.exit_status = 0;
	g_mini.in_command = 0;
	return (loop_main(envs));
	(void)argc;
	(void)argv;
	(void)envs;
}
