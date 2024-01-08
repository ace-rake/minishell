/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:08:30 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/08 13:32:47 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next_node;

	if (!lst || !del)
	{
		return ;
	}
	temp = *lst;
	while (temp)
	{
		next_node = temp->next;
		ft_lstdelone(temp, del);
		temp = next_node;
	}
	*lst = NULL;
}
