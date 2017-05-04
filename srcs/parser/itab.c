/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:53:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/11 04:58:36 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		*new_indexes(int i0, int i1)
{
	int *idxs;

	if ((idxs = (int*)malloc(sizeof(int) * 2)) == NULL)
		return (NULL);
	idxs[0] = i0;
	idxs[1] = i1;
	return (idxs);
}

int		**new_itab(int i0, int i1)
{
	int **itab;

	if ((itab = (int**)malloc(sizeof(int*) * 2)) == NULL)
		return (NULL);
	itab[1] = NULL;
	if ((itab[0] = new_indexes(i0, i1)) == NULL)
	{
		ft_memdel((void **)&itab);
		return (NULL);
	}
	return (itab);
}

size_t	itab_len(int **itab)
{
	size_t i;

	if (itab == NULL || *itab == NULL)
		return (0);
	i = 0;
	while (itab[i])
		i++;
	return (i);
}

void	itab_del(int ***itab)
{
	size_t	len;
	size_t	i;

	if (!itab || !*itab)
		return ;
	len = itab_len(*itab);
	i = 0;
	while (i < len)
	{
		ft_memdel((void **)&(*itab)[i]);
		i++;
	}
	ft_memdel((void **)&*itab);
	*itab = NULL;
}

int		itab_push(int ***itab, int i0, int i1)
{
	size_t	i;
	size_t	len;
	int		**newone;

	if (*itab == NULL)
		*itab = new_itab(i0, i1);
	else
	{
		i = 0;
		len = itab_len(*itab) + 1;
		if ((newone = (int**)malloc(sizeof(int*) * len * 2)) == NULL)
			return (-1);
		newone[len] = NULL;
		while (i < len)
		{
			if (i == len - 1)
				newone[i] = new_indexes(i0, i1);
			else
				newone[i] = new_indexes((*itab)[i][0], (*itab)[i][1]);
			i++;
		}
		itab_del(itab);
		*itab = newone;
	}
	return (0);
}
