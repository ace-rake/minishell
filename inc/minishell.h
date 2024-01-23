
#ifndef MINISHELL_H
# define MINISHELL_H

#include "typedefs.h"
#include "tokenizer.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env_parser.h"
#include "../libft/inc/libft.h"

#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

extern volatile sig_atomic_t g_in_command;

#endif
