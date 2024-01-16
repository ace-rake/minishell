#ifndef ENV_PARSER_H
# define ENV_PARSER_H

#include <unistd.h>
#include "../../inc/typedefs.h"
#include <stdlib.h>
#include <string.h>
#include "../executor/executor.h"


#include "../lexer/libft/inc/libft.h"
#include "../lexer/libft/inc/get_next_line.h"



t_env_list *env_parser(char *env[]);
void	free_env(t_env_list *env);
t_env_list	*del_node(t_env_list **head, t_env_list *to_del);
t_env_list	*get_env_node(t_env_list *head, char *var);
void env_add_back(t_env_list **head, t_env_list *to_add);
t_env_list	*env_node_con(char *var, char *val, bool exported);

#endif
