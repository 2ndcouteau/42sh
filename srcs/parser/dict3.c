/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:26:01 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/25 21:11:11 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			dict_del(t_dict *dict, char *key)
{
	t_cell	*cell;

	if ((cell = dict_pop(dict, key)) != NULL)
		del_cell(&cell);
}

void			del_head_cell(t_head *head)
{
	t_cell *cell;

	cell = GET_NODE(head, t_cell, head);
	del_cell(&cell);
}

void			destroy_dict(t_dict **dict)
{
	size_t	i;
	t_cell	*cell;

	i = 0;
	if (!dict || !*dict)
		return ;
	while (i < (*dict)->size)
	{
		if ((cell = (*dict)->cells[i]) != NULL)
			list_iter(&(cell->head), &del_head_cell);
		i++;
	}
	ft_memdel((void **)&(*dict)->cells);
	ft_memdel((void **)&(*dict));
	(*dict) = NULL;
}

size_t			dict_len(t_dict **dict)
{
	size_t	i;
	size_t	len;
	t_cell	*cell;

	i = 0;
	len = 0;
	if (dict && *dict)
		while (i < (*dict)->size)
		{
			if ((cell = (*dict)->cells[i]) != NULL)
				len += list_len(&(cell->head));
			i++;
		}
	return (len);
}

void			dict_iter(t_dict *dict, void (*fct)(t_head *))
{
	size_t i;
	t_cell *cells;

	i = 0;
	if (dict->cells != NULL)
	{
		while (i < dict->size)
		{
			if ((cells = dict->cells[i]) != NULL)
				list_iter(&(cells->head), fct);
			i++;
		}
	}
}
