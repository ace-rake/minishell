#include "typedefs.h"
#include "tokenizer.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char **argv) {
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
    return 0;
}

