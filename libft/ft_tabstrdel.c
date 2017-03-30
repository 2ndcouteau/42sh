/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:46:28 by nboulaye          #+#    #+#             */
/*   Updated: 2016/11/07 07:48:38 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_tabstrdel(char **t)
{
	if (*t)
		ft_tabstrdel(t + 1);
	free(*t);
	*t = NULL;
}

void	ft_freetab(char ***t)
{
	ft_tabstrdel(*t);
	free(*t);
	*t = NULL;
}
