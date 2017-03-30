/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:29:26 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/29 11:21:42 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putstrstr(char *s1, char *s2)
{
	ft_putstr(s1);
	ft_putstr(s2);
}

void				ft_putnbrstr(int nb, char *s2)
{
	ft_putnbr(nb);
	ft_putstr(s2);
}

void				ft_putstrnbr(char *s1, int nbr)
{
	ft_putstr(s1);
	ft_putnbr(nbr);
}

void				ft_putstrnbrstr(char *s1, int nbr, char *s2)
{
	ft_putstr(s1);
	ft_putnbr(nbr);
	ft_putstr(s2);
}

void				ft_putstrstrstr(char *s1, char *s2, char *s3)
{
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
}
