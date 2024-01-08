/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:00:44 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/08 13:41:40 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

long long	ft_max(long long a, long long b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
