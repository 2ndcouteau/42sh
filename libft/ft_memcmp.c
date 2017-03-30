/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:17:05 by nboulaye          #+#    #+#             */
/*   Updated: 2015/11/28 17:47:21 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if ((((char *)s1)[i]) != (((char *)s2)[i]))
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
