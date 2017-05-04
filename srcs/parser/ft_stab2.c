/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stab2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:50:51 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/18 21:57:54 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_stabpop(char ***stab, size_t idx)
{
	char	**ret;
	size_t	len;
	size_t	i;

	if ((*stab) == NULL)
		return (-1);
	len = ft_stablen((*stab));
	if (len == 1)
		return (-1);
	if ((ret = (char **)ft_memalloc(sizeof(char*) * len)) == NULL)
		return (-1);
	ret[len - 1] = 0;
	i = 0;
	while ((*stab)[i])
	{
		if (i != idx)
			ret[i - (i > idx)] = ft_strdup((*stab)[i]);
		i++;
	}
	ft_stabdel(stab);
	(*stab) = ret;
	return (0);
}

int		ft_stabupd(char ***stab, size_t idx, char *entry)
{
	char	*tmp;
	size_t	len;

	len = ft_stablen(*stab);
	if (idx > len)
		return (-1);
	if ((tmp = ft_strdup(entry)) == NULL)
		return (-1);
	ft_strdel(&(*stab)[idx]);
	(*stab)[idx] = tmp;
	return (0);
}

size_t	ft_stablen(char *const *stab)
{
	size_t	i;

	if (!stab)
		return (0);
	i = 0;
	while (stab[i])
		i++;
	return (i);
}
