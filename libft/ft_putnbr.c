/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 21:15:39 by nboulaye          #+#    #+#             */
/*   Updated: 2016/02/01 22:15:28 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	size_t	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (n / 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}