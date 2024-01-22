#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\nminishell: ", 12);
}

int	loop_main(char *envs[])
{
    t_token **tokens;
    t_token *ast_head;
	t_env_list *env;
	char *input;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			return (1);
		add_history(input);
   		tokens = tokenizer(input);
		if (!lexer(tokens))
		{
			//TODO: free tokens
			return (1);
		}
   		ast_head = parser(tokens);
	
		env = env_parser(envs);
		exec_token(ast_head, env);	
	}
	free_env(env);

	return (0);
}

int main(int argc, char **argv, char *envs[]) {
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	return (loop_main(envs));
	(void)argc;
	(void)argv;
	(void)envs;
}
