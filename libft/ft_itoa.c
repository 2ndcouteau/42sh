/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:34:35 by nboulaye          #+#    #+#             */
/*   Updated: 2016/11/06 22:08:26 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int n)
{
	int				nbdigit;
	char			*str;
	unsigned int	unsignn;

	unsignn = (n < 0) ? -n : n;
	nbdigit = (n < 0) ? 2 : 1;
	while ((unsignn = unsignn / 10))
		nbdigit++;
	unsignn = (n < 0) ? -n : n;
	if (!(str = ft_strnew(nbdigit)))
		return (NULL);
	while (nbdigit--)
	{
		str[nbdigit] = (unsignn % 10 + '0');
		unsignn /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
