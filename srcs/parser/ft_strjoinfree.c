/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 15:21:04 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/20 14:29:29 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char		*tmp1;

	tmp1 = s1;
	s1 = ft_strjoin(tmp1, s2);
	ft_strdel(&tmp1);
	ft_strdel(&s2);
	return (s1);
}
