/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:26:32 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/19 14:42:36 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	del_str_value(void *val)
{
	ft_memdel((void **)&val);
}

t_dict	*env2dict(char **env)
{
	int		idx;
	t_dict	*d;
	char	*ptr;
	t_cell	*cell;

	if ((d = new_dict(_SIZE_ENV_DICT)) == NULL)
		return (NULL);
	idx = -1;
	while (env[++idx])
	{
		if ((ptr = ft_strchr(env[idx], '=')) && ++ptr)
		{
			if ((cell = new_cell(ft_strndup(env[idx], ptr - env[idx] - 1),
				ft_strdup(ptr), &del_str_value)) == NULL ||
				cell->key == NULL)
				del_cell(&cell);
			else
				dict_set(d, cell);
		}
	}
	return (d);
}

t_cell	*dict_next(t_dict *d, t_cell *cur)
{
	t_cell	*line;
	int		h;

	if (d == NULL)
		return (NULL);
	line = NULL;
	h = 0;
	if (cur == NULL)
		line = d->cells[0];
	else if (cur->head.next != NULL)
		return (GET_NODE(cur->head.next, t_cell, head));
	if (line == NULL && cur)
	{
		h = (key_hash(cur->key) % d->size) + 1;
		if (h >= (int)d->size)
			return (NULL);
		line = d->cells[h + 1];
	}
	while (h < (int)d->size)
	{
		if (d->cells[h] != NULL)
			return (d->cells[h]);
		h++;
	}
	return (NULL);
}
