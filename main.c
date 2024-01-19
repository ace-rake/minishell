#include "typedefs.h"
#include "tokenizer.h"
#include "lexer.h"
#include "parser.h"
#include "src/executor/executor.h"
#include "src/prep/env_parser.h"

int main(int argc, char **argv, char *envs[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s 'command'\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    t_token **tokens;
    t_token *ast_head;

    tokens = tokenizer(input);
    lexer(tokens);
    ast_head = parser(tokens);

	t_env_list *env = env_parser(envs);
	exec_token(ast_head, env);	
    return 0;
}

