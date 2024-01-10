#ifndef ENV_PARSER_H
# define ENV_PARSER_H

#include <unistd.h>
#include "../../inc/typedefs.h"
#include <stdlib.h>
#include <string.h>
#include "../executor/executor.h"


#include "../lexer/libft/inc/libft.h"



t_env_list *env_parser(char *env[]);
void	free_env(t_env_list *env);

#endif
