/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:25:23 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/18 17:14:26 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			push_cell2(t_cell **cells, t_cell *cell)
{
	if ((*cells) == NULL)
		(*cells) = cell;
	else
	{
		list_append(&(cell->head), &((*cells)->head));
		(*cells) = cell;
	}
}

void			dict_set(t_dict *dict, t_cell *cell)
{
	t_cell	*poped;
	t_cell	**cells;
	t_head	*tmp;

	poped = NULL;
	cells = &(dict->cells[(key_hash(cell->key) % dict->size)]);
	if ((*cells) != NULL && (tmp = list_get_first(&((*cells)->head),
			(void*)cell->key, &cmp_cell_keys)) != NULL)
		poped = GET_NODE(tmp, t_cell, head);
	if (poped)
	{
		if (poped == (*cells))
		{
			list_replace_one(&(poped->head), &(cell->head));
			(*cells) = cell;
		}
		else
		{
			push_cell2(cells, cell);
			list_pop_one(&(poped->head));
		}
		del_cell(&poped);
	}
	else
		push_cell2(cells, cell);
}

void			dict_set_doublon(t_dict *dict, t_cell *cell)
{
	t_cell	**cells;
	t_head	*tmp;

	cells = &(dict->cells[(key_hash(cell->key) % dict->size)]);
	if ((*cells) != NULL && (tmp = list_get_first(&((*cells)->head),
	(void*)cell->key, &cmp_cell_keys)) != NULL)
		(void)tmp;
	push_cell(cells, cell);
}

t_cell			*dict_get(t_dict *dict, char *key)
{
	t_cell	*cells;
	t_head	*tmp;

	cells = dict->cells[(key_hash(key) % dict->size)];
	if (cells == NULL ||
		(tmp = list_get_first(&(cells->head),
			(void*)key, &cmp_cell_keys)) == NULL)
		return (NULL);
	return (GET_NODE(tmp, t_cell, head));
}
