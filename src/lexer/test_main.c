#include "lexer.h"
#include <stdio.h> 
#include <stdlib.h> 

 int main() { 
     const char *test_str = "> output.txt echo hello | cat"; 

     t_token **tokens = tokenize(test_str); 
     if (tokens == NULL) { 
         fprintf(stderr, "Tokenization failed.\n"); 
         return (1); 
     } 

     lexer(tokens); 

     for (int i = 0; tokens[i] != NULL; i++) { 
         printf("Token: %s, Type: %d\n", tokens[i]->value,
	tokens[i]->type); 
         free(tokens[i]->value); 
         free(tokens[i]); 
     } 
     free(tokens); 

     return (0); 
 } 
