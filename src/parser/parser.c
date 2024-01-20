/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:29:23 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/20 15:26:56 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*parser(t_token **tokens)
{
	t_token *ast_head;
	t_token	*ret1;
	t_token	*ret2;
	t_token	*ret3;
	t_token	*ret4;

	ast_head = NULL;
	ret1 = parse_pipes(tokens);
	ret2 = parse_redirections(tokens);
	ret3 = parse_commands(tokens);
	ret4 = parse_arguments(tokens);
	if (ret1)
		ast_head = ret1;
	else if (ret2)
		ast_head = ret2;
	else if (ret3)
		ast_head = ret3;
	else if (ret4)
		ast_head = ret4;
	return (ast_head);
}

#include "typedefs.h" // Replace with the correct header files for your project
#include "tokenizer.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

// Function to recursively print the syntax tree
void print_tree(t_token *token, int level) {
    if (token == NULL)
        return;

    // Print the current token
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Value: %s, Type: %d\n", token->value, token->type);

    // Recursively print left and right children
    print_tree(token->left, level + 1);
    print_tree(token->right, level + 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Tokenize the input string
    t_token **tokens = tokenizer(argv[1]);
    if (tokens == NULL) {
        fprintf(stderr, "Tokenization failed.\n");
        return 1;
    }

    // Process tokens through lexer
    if (!lexer(tokens))
		return (1);

    // Parse the tokens into a syntax tree
    t_token *ast_head = parser(tokens);

    // Print the syntax tree
    print_tree(ast_head, 0);

    // Free the syntax tree and tokens
    // (Add your memory cleanup code here)

    return 0;
}

