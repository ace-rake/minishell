/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 08:37:31 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/05 12:47:57 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

//// TYPES OF TOKENS
// @PIPE			|
// @REDIR_IN		<
// @REDIR_OUT		>
// @REDIR_HEREDOC	<<
// @REDIC_APPEND	>>
// @COMMAND			builtin or PATH
// @ARGUMENT		all other
typedef enum e_token_type
{
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
typedef struct s_token
{
	t_token_type	type;
	t_quoting_status	quoting_status;
	char			*value;
	struct s_token	*left;
	struct s_token	*right;
	struct s_token	*parent;
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

#endif
