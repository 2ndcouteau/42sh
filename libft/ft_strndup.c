/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 11:43:53 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/07 11:48:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char *s2;

	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (n--)
		s2[n] = s1[n];
	return (s2);
}
