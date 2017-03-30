/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 23:02:11 by nboulaye          #+#    #+#             */
/*   Updated: 2016/04/07 23:41:31 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}
