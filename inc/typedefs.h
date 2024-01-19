#ifndef TYPEDEFS_H
# define TYPEDEFS_H

#include <stdbool.h>

//// TYPES OF TOKENS
// @UNDEFINED		not yet set
// @PIPE			|
// @REDIR_IN		<
// @REDIR_OUT		>
// @REDIR_HEREDOC	<<
// @REDIC_APPEND	>>
// @COMMAND			builtin or PATH
// @ARGUMENT		all other
typedef enum e_token_type
{
	UNDEFINED,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
	COMMAND,
	ARGUMENT
}					t_token_type;

//// QUOTING STATUS
// @UNQUOTED		default
// @SINGLE_QUOTED	no metacharacters interpreted
// @DOUBLE QUOTED	no metacharacters interpreted except for $
typedef enum e_quoting_status
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
}					t_quoting_status;

//// TOKEN STRUCT
// @type		pipe/redic(*)/cmd/arg	
// @status		unquoted/''/""
// @value		string
// @left		left child node
// @right		right child node
// @parent		parent node
// @input		takes input from..
// @output		sends output to..
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*left;
	struct s_token	*right;
	struct s_token	*parent;// im using this one for exit
	short			input;
	short			output;
}					t_token;

typedef struct s_tokenizer_utils
{
	int size;
	int capacity;
	int	start;
	int	current;
	char c;
	t_quoting_status quoting_status;
	t_token **tokens;
}					t_tokenizer_utils;

typedef struct s_parser_utils_redir
{
	t_token	*last_redirection;
	t_token	*first_redirection;
	t_token	*pipe;
	int		i;
}					t_parser_utils_redir;


typedef	struct	s_env_list
{
	bool	exported;
	char *var;
	char *val;
	struct s_env_list *next;
}				t_env_list;

#endif
