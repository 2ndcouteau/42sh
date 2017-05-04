/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 00:02:53 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/26 16:44:11 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_stabnew(size_t size)
{
	char **stab;

	if (!(stab = (char**)ft_memalloc((sizeof(char*) * size))))
		return (NULL);
	return (stab);
}

char	**ft_stabdup(char *const *stab)
{
	char	**ret;
	size_t	i;

	i = 0;
	ret = (char**)ft_memalloc(sizeof(char*) * (ft_stablen(stab) + 1));
	while (stab[i])
	{
		ret[i] = ft_strdup(stab[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	ft_stabdel(char ***stab)
{
	int i;

	i = -1;
	while ((*stab)[++i])
		ft_memdel((void **)&(*stab)[i]);
	ft_memdel((void **)&(*stab));
	*stab = NULL;
}

int		ft_stabpush(char ***stab, char *entry)
{
	char	**ret;
	size_t	i;
	size_t	len;

	i = 0;
	if ((*stab) == NULL)
		len = 0;
	else
		len = ft_stablen((*stab));
	if ((ret = (char **)ft_memalloc(sizeof(char*) * (len + 2))) == NULL)
		return (-1);
	ret[len + 1] = 0;
	while ((*stab) != NULL && (*stab)[i])
	{
		ret[i] = ft_strdup((*stab)[i]);
		i++;
	}
	ret[i] = ft_strdup(entry);
	if ((*stab) != NULL)
		ft_stabdel(stab);
	(*stab) = ret;
	return (0);
}
