/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:34:37 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/10 13:36:41 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*parse_pipes(t_token **tokens)
{
	t_token *head;
	t_token	*prev_pipe;
	int		i;

	head = NULL;
	prev_pipe = NULL;
	i = 0;
	while (tokens[i++]);
	while (i--)
	{
		if (tokens[i]->type == PIPE)
		{
			if (head == NULL)
				head = tokens[i];
			else
			{
				tokens[i]->parent = prev_pipe;
				prev_pipe->left = tokens[i];
			}
			prev_pipe = tokens[i];
		}
	}
	return (head);
}
