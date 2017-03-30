/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 00:18:48 by nboulaye          #+#    #+#             */
/*   Updated: 2016/02/01 22:15:55 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putnbr_fd(int n, int fd)
{
	size_t	nb;
	char	c;

	nb = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (n / 10)
		ft_putnbr_fd(nb / 10, fd);
	c = (nb % 10 + '0');
	write(fd, &c, 1);
}
