/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:43:24 by nboulaye          #+#    #+#             */
/*   Updated: 2016/05/17 00:19:50 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strntrim(const char *s, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (len > i)
		while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
			len--;
	if (!(str = ft_strsub(s, i, len - i)))
		return (void *)0;
	str[len - i] = '\0';
	return (str);
}
