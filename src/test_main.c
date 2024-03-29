/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:10:08 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 13:10:53 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "../inc/minishell.h"

t_mini	g_mini;


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
		if (ft_strcmp(input, "exit") == 0)
			break;
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
		 printf("retval main : [%i]\n",retval);
		free_tokens(tokens);
		if (wait)
		{
			str = readline("\nnext ? [q to stop]");
			if (ft_strcmp(str, "q") == 0)
				break ;
			str = 0;
		}
	}
	fclose(file);
	free_env(env);

	return (0);
}

int main(int argc, char **argv, char *envs[]) {
	 rl_catch_signals = 0; 
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	printf("choices :\n1 : run all comands rapid fire\n2 : run all 
	commands step by step\n3 : run non input commands rapid fire\n4 
	: run non input commands step by step\n");
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
	if (option == 5)
		cmd_main("new_commands.txt", envs, false);
	if (option == 6)
		cmd_main("new_commands.txt", envs, true);
	(void)argc;
	(void)argv;
	(void)envs;
}
*/
