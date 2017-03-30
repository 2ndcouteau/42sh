/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:05:06 by nboulaye          #+#    #+#             */
/*   Updated: 2015/11/29 16:42:41 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if ((*(unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		s += 1;
		n--;
	}
	return (NULL);
}
