/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_fd_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:29:26 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/29 11:22:32 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putstrstr_fd(char *s1, char *s2, int fd)
{
	return (ft_putstr_fd(s1, fd) + ft_putstr_fd(s2, fd));
}

int			ft_putnbrstr_fd(int nb, char *s2, int fd)
{
	ft_putnbr_fd(nb, fd);
	return (ft_putstr_fd(s2, fd));
}

int			ft_putstrnbr_fd(char *s1, int nbr, int fd)
{
	size_t	i;

	i = ft_putstr_fd(s1, fd);
	ft_putnbr_fd(nbr, fd);
	return (i);
}

int			ft_putstrnbrstr_fd(char *s1, int nbr, char *s2, int fd)
{
	size_t	i;

	i = ft_putstr_fd(s1, fd);
	ft_putnbr_fd(nbr, fd);
	i += ft_putstr_fd(s2, fd);
	return (i);
}

int			ft_putstrcharstr_fd(char *s1, char c, char *s2, int fd)
{
	size_t	i;

	i = ft_putstr_fd(s1, fd);
	ft_putchar_fd(c, fd);
	i += ft_putstr_fd(s2, fd);
	return (i);
}
