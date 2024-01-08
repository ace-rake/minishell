/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:16 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/08 14:44:09 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../inc/typedefs.h"

//this token is the first ARG token
//converts the chain of token ARGS to a single array
//only the char ** needs freeing, as all the char * are pointers to the token values
char **token_chain_to_array(t_token *token);


#endif
