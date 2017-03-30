/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 03:35:34 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/03 23:22:55 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char	*ret;
	size_t	i;

	if (!s || !f || !(ret = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*s)
	{
		ret[i] = (f)(*s);
		s++;
		i++;
	}
	return (ret);
}
