/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 17:08:39 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/25 22:19:56 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_str_dict(t_dict *dct)
{
	t_cell	*iterator;

	iterator = NULL;
	while ((iterator = dict_next(dct, iterator)) != NULL)
	{
		ft_printf("%s=\"%s\"\n", iterator->key, iterator->value);
	}
}

void	push_cell(t_cell **cells, t_cell *cell)
{
	if ((*cells) == NULL)
		(*cells) = cell;
	else
		list_append(&((*cells)->head), &(cell->head));
}

void	free_cell(t_cell *cell_tofree)
{
	free(cell_tofree->value);
	free(cell_tofree->key);
	free(cell_tofree);
}

void	dict_pop_middl(t_dict *dict, char *key)
{
	t_cell	**cells;
	t_cell	*cell;
	t_cell	*cell_tofree;
	t_cell	*cells_new;

	cells_new = NULL;
	cells = &(dict->cells[(key_hash(key) % dict->size)]);
	cell = (dict->cells[(key_hash(key) % dict->size)]);
	while (cell)
	{
		if (!ft_strequ(cell->key, key))
		{
			if (cells_new == NULL)
				cells_new = new_cell(ft_strdup((cell)->key),
					ft_strdup((cell)->value), &free);
			else
				list_append(&cells_new->head, &new_cell(ft_strdup((cell)->key),
					ft_strdup((cell)->value), &free)->head);
		}
		cell_tofree = cell;
		cell = (cell->head.next) ?
			GET_NODE((cell->head.next), t_cell, head) : NULL;
		free_cell(cell_tofree);
	}
	dict->cells[(key_hash(key) % dict->size)] = cells_new;
}

t_cell	*dict_pop(t_dict *dict, char *key)
{
	t_cell *c;
	t_head *hc;

	if (!(c = dict_get(dict, key)))
		return (NULL);
	if (c->head.prev == NULL)
	{
		hc = &(c->head);
		list_pop_first(&hc);
		if (hc == NULL)
			dict->cells[(key_hash(c->key) % dict->size)] = NULL;
		else
			dict->cells[(key_hash(c->key) % dict->size)] =
				GET_NODE(hc, t_cell, head);
	}
	else
	{
		dict_pop_middl(dict, key);
		return (NULL);
	}
	return (c);
}
