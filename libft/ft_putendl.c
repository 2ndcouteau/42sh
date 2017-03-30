/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:49:52 by nboulaye          #+#    #+#             */
/*   Updated: 2016/04/10 04:39:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putendl(const char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	else
	{
		i = write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
	return (i);
}
