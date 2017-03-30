/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 03:47:57 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/03 23:23:24 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!s || !f || !(ret = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		ret[i] = (f)(i, s[i]);
		i++;
	}
	return (ret);
}
