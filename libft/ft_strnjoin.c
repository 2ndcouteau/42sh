/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:07:03 by nboulaye          #+#    #+#             */
/*   Updated: 2016/07/10 13:34:45 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(const char *s1, const char *s2, size_t i)
{
	char	*ret;

	if (!s1 || !s2 || !i || !(ret = ft_strnew(ft_strlen(s1) + i)))
		return (NULL);
	ret = ft_strcpy(ret, s1);
	ret = ft_strncat(ret, s2, i);
	return (ret);
}
