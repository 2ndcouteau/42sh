/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:10:43 by nboulaye          #+#    #+#             */
/*   Updated: 2016/03/28 18:32:21 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s || (!(ret = ft_strnew(len))))
		return (NULL);
	while (len--)
		ret[len] = s[start + len];
	return (ret);
}
