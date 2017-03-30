/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:34:35 by nboulaye          #+#    #+#             */
/*   Updated: 2016/08/30 18:13:37 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa_base(long double value, int base)
{
	int				nbdigit;
	char			*str;
	unsigned int	unsignn;

	if (base < 2 || base > 16)
		return ((void *)0);
	unsignn = (value < 0) ? -value : value;
	nbdigit = (value < 0 && base == 10) ? 2 : 1;
	while ((unsignn = unsignn / base))
		nbdigit++;
	unsignn = (value < 0) ? -value : value;
	if (!(str = ft_strnew(nbdigit)))
		return (NULL);
	str[--nbdigit] = (unsignn % base > 9) ? (unsignn % base + 'A' - 10)
		: (unsignn % base + '0');
	while ((unsignn = unsignn / base) > 0)
		str[--nbdigit] = (unsignn % base > 9) ? (unsignn % base + 'A' - 10)
			: (unsignn % base + '0');
	if (value < 0 && base == 10)
		str[0] = '-';
	return (str);
}
