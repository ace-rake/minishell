/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:20:02 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/05 15:54:14 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	g_mini.exit_status = 130;
	if (!g_mini.in_command)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
