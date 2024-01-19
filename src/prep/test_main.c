#include "env_parser.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
/*
void	env_test(char **env)
{

	t_env_list *env_list  = env_parser(env);
	t_token *token = malloc(sizeof(t_token));
	token->type = COMMAND;
	token->value = "env";
	token->output = open("create_test", O_WRONLY|O_CREAT);
	token->input = 0;
	env_builtin(token, env_list);
}
*/
//0 = read
//1 = write
void	rl_test(void)
{
	char *str;
	int	filedes[2];

	int retval = pipe(filedes);
	(void)retval;

	while ((str = readline(">>")) != NULL)
	{
		ft_putendl_fd(str, filedes[1]);
		if (ft_strcmp(str, "EOF") == 0)
			break ;
		add_history(str);
	}
	//TODO handle cntrl + d sign
	while ((str = get_next_line(filedes[0])) != NULL)
	{
		if (ft_strcmp(str, "EOF") == 0)
			break ;
		ft_putstr_fd(str, 1);
	}
}

#include <readline/readline.h>
#include <readline/history.h>

void history_test() {
	char *str = readline("fuck you:");
	printf("%s", str);
	add_history(str);
	str = readline("fuck you:");
	printf("%s", str);
	add_history(str);
	str = readline("fuck you:");
	printf("%s", str);
	add_history(str);
	str = readline("fuck you:");
	printf("%s", str);

}

void	history_test2()
{
	char *str;
	while ((str = readline(">>")) != NULL)
	{
		if (ft_strcmp(str, "EOF") == 0)
			break ;
		if (ft_strcmp(str, "CLEAR") == 0)
			rl_clear_history();
		ft_putendl_fd(str, 1);
		add_history(str);
	}
}

void	replace_line_test()
{
	char *str = readline(">>");
	printf("%s", str);
	rl_replace_line("replacement", 0);
	rl_redisplay();
}



int	main(int argc, char *argv[], char *env[])
{

}
