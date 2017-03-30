/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 00:30:21 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/08 15:24:53 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	char	*ret;
	int		idx;

	if (!str || !(ret = ft_strnew(ft_strlen(str))))
		return (NULL);
	idx = -1;
	while (str[++idx])
		ret[idx] = ft_tolower(str[idx]);
	return (ret);
}
