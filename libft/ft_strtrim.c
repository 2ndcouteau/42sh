/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:43:24 by nboulaye          #+#    #+#             */
/*   Updated: 2016/03/28 19:33:47 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (j > i)
		while (s[j - 1] == ' ' || s[j - 1] == '\n' || s[j - 1] == '\t')
			j--;
	if (!(str = ft_strsub(s, i, j - i)))
		return (void *)0;
	str[j - i] = '\0';
	return (str);
}
