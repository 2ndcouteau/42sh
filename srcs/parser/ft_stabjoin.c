/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stabjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:56:48 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/21 18:11:00 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*make_it(char **stab, char *sep, size_t size)
{
	int		i;
	char	*ret;

	i = -1;
	if ((ret = (char*)ft_memalloc(sizeof(char) * size)) == NULL)
		return (NULL);
	while (stab[++i])
	{
		ft_strcat(ret, stab[i]);
		if (stab[i + 1] != 0)
			ft_strcat(ret, sep);
	}
	return (ret);
}

char		*ft_stabjoin(char *sep, char **stab)
{
	size_t	len;
	int		i;
	size_t	size;
	size_t	sep_size;

	sep_size = ft_strlen(sep);
	len = ft_stablen(stab);
	if (!len)
		return (NULL);
	if (len == 1)
		return (ft_strdup(stab[0]));
	size = 0;
	i = -1;
	while (stab[++i])
		size += ft_strlen(stab[i]) + (stab[i + 1] != 0 ? sep_size : 0);
	return (make_it(stab, sep, size));
}
