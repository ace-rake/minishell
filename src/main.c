#include "../inc/minishell.h"

int	input_main(int argc, char *argv[], char *envs[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s 'command'\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    t_token **tokens;
    t_token *ast_head;

    tokens = tokenizer(input);
	if (!lexer(tokens))
	{
		//TODO: free tokens
		return (1);
	}
    ast_head = parser(tokens);

	t_env_list *env = env_parser(envs);
	exec_token(ast_head, env);	
	free_env(env);
    return (0);

}

#include <readline/readline.h>
#include <readline/history.h>


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
	return (loop_main(envs));
	(void)argc;
	(void)argv;
	(void)envs;
}
