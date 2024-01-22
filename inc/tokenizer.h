
#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "typedefs.h"
# include "../libft/inc/libft.h"
# include <stddef.h>
# include <stdlib.h>

//tokenize.c
int		init_tokenizer_utils(t_tokenizer_utils *u);
t_token	*create_token(char *token_value);
t_token	**add_token(t_tokenizer_utils *u, char *token_value);
t_token **tokenizer(const char *input);

//tokenize_handlers.c
void	handle_special_char(const char *input, t_tokenizer_utils *u);
void	handle_whitespace(const char *input, t_tokenizer_utils *u);
void	handle_single_quote(t_tokenizer_utils *u);
void	handle_double_quote(t_tokenizer_utils *u);
void	handle_last_token(const char *input, t_tokenizer_utils *u);

#endif
