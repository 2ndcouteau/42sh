/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 00:34:47 by nboulaye          #+#    #+#             */
/*   Updated: 2015/11/29 19:29:33 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	i;
	size_t	lendst;

	i = 0;
	l = 0;
	lendst = 0;
	while (dst[l] != '\0' && l < size)
	{
		l++;
		lendst++;
	}
	while (src[i] && l < (size - 1))
	{
		dst[l] = src[i];
		l++;
		i++;
	}
	if (l > lendst)
		dst[l] = '\0';
	if (!src[i])
		return (l);
	return (lendst + ft_strlen(src));
}
