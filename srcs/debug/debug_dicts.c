/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_dicts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 20:07:26 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 20:22:23 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	put_dct_elem(t_head *cellhead)
{
	t_cell	*cell;

	cell = GET_NODE(cellhead, t_cell, head);
	ft_fdprintf(g_debug[1], " %s=\"%s\"", cell->key, cell->value);
}

void	debug_dict(t_dict *dct)
{
	ssize_t	icells;
	t_cell	*cells;

	ft_fdprintf(g_debug[1], "== dbg dct ==\n");
	if (g_debug[0])
	{
		ft_fdprintf(g_debug[1], "dsize: %lu", dct->size);
		icells = -1;
		while ((size_t)++icells < dct->size)
		{
			ft_fdprintf(g_debug[1], "%ld:", icells);
			if ((cells = dct->cells[icells]) != NULL)
				list_iter(&(cells)->head, &put_dct_elem);
			ft_putchar_fd('\n', g_debug[1]);
		}
	}
}
