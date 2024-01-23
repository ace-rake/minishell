#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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

	env = env_parser(envs);

	while (1)
	{
		input = readline("minishell: ");
		//TODO check for empty input
		if (!input)
		{
			//ctrl-D
			printf("exit\n");
			break ;
		}
		add_history(input);
   		tokens = tokenizer(input);
		free(input);
		if (!lexer(tokens))
		{
			//TODO: free tokens
			return (1);
		}
   		ast_head = parser(tokens);
	
		int	retval = executor(ast_head,env);
		/* printf("retval main : [%i]\n",retval); */	
		if (retval == 7)
			exit(0);
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
