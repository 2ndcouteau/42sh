/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 23:08:11 by nboulaye          #+#    #+#             */
/*   Updated: 2016/04/10 06:09:43 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putendl_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
		i = write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	return (i + 1);
}
