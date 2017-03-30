/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 19:18:01 by nboulaye          #+#    #+#             */
/*   Updated: 2016/08/30 01:37:35 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnstr(const char *s, int i)
{
	if (s)
		write(1, s, i);
	else
		write(1, "(null)", 6);
}

void	ft_putnstr_fd(const char *s, int i, int fd)
{
	if (s)
		write(fd, s, i);
	else
		write(fd, "(null)", 6);
}
