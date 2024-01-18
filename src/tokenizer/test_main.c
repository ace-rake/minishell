
#include "tokenizer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void	test1(){
    const char *input = "echo Hello'World";
    t_token **tokens = tokenizer(input);

    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token: %s\n", tokens[i]->value);
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

void	test2()
{
	const char *str;
    t_token **tokens;
	while ((str = readline(">>")) != NULL)
	{
		if (ft_strcmp(str, "EOF") == 0)
			break ;
		tokens = tokenizer(str);
   	 	int i = 0;
   		while (tokens[i] != NULL) {
        	printf("Token: %s\n", tokens[i]->value);
        	free(tokens[i]->value);
        	free(tokens[i]);
        	i++;
    	}
    	free(tokens);
	}
}

void	test3()
{
	char str[100];
    t_token **tokens;
	FILE *file = fopen("commands.txt", "r");
	while (fscanf(file, " %[^\n]", str) == 1)
	{
		tokens = tokenizer(str);
   	 	int i = 0;
		printf("input string : [%s]\n", str);
   		while (tokens[i] != NULL) {
        	printf("Token: %s\n", tokens[i]->value);
        	free(tokens[i]->value);
        	free(tokens[i]);
        	i++;
    	}
    	free(tokens);
		printf("\n");
	}
}

int main()
{
	test3();

}

