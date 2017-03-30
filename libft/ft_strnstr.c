/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:21:48 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/30 00:24:53 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	j = 0;
	k = 0;
	if (!(s2[i]))
		return ((char *)&s1[i]);
	while (s1[i] && i <= n)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k++] == s2[j++] && k <= n)
			{
				if (!s2[j])
					return ((char *)&s1[i]);
			}
		}
		j = 0;
		i++;
	}
	return (NULL);
}
