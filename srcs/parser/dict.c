/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:42:15 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/23 18:13:56 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				key_hash(char *key)
{
	int	hash;

	if (!key)
		return (0);
	hash = 0;
	while (*key != 0)
	{
		hash += (*key);
		key++;
	}
	return (hash);
}

t_cell			*new_cell(char *key, void *value, void (*del_value)(void*))
{
	t_cell *cell;

	if ((cell = (t_cell*)ft_memalloc(sizeof(t_cell))) == NULL)
		return (NULL);
	cell->key = key;
	cell->value = value;
	cell->del_value = del_value;
	return (cell);
}

void			del_cell(t_cell **cell)
{
	if ((*cell) != NULL)
	{
		if ((*cell)->key != NULL)
			ft_strdel(&((*cell)->key));
		if ((*cell)->del_value != NULL && (*cell)->value != NULL)
			(*cell)->del_value((*cell)->value);
		ft_memdel((void **)&(*cell));
		cell = NULL;
	}
}

t_dict			*new_dict(size_t dsize)
{
	t_dict	*dct;

	if (dsize == 0)
		return (NULL);
	if ((dct = (t_dict*)ft_memalloc(sizeof(t_dict))) == NULL)
		return (NULL);
	if ((dct->cells = (t_cell**)ft_memalloc(sizeof(t_cell*) * dsize)) == NULL)
	{
		ft_memdel((void **)&dct);
		return (NULL);
	}
	dct->size = dsize;
	return (dct);
}

char			cmp_cell_keys(t_head *head, void *key)
{
	t_cell	*cell;

	if (head == NULL ||
		(cell = GET_NODE(head, t_cell, head)) == NULL)
		return ((char)0);
	if (key == NULL && cell->key == NULL)
		return (1);
	if (key == NULL || cell->key == NULL)
		return (0);
	return ((char)(ft_strcmp(cell->key, (char*)key) == 0));
}
