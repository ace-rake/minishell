/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:27:42 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/08 13:24:02 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_free_array(char **array, size_t size)
{
	if (!array)
		return ;
	while (size--)
	{
		if (array[size] != NULL)
		{
			free(array[size]);
			array[size] = NULL;
		}
	}
	free(array);
}
